#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "8080emuCPP.h"
#include "gtuos.h"

using std::hex;
using std::cout;
using std::cin;
using std::endl;
using std::string;

uint64_t GTUOS::handleCall(CPU8080 & cpu, int cycleCount){
	//Address from B AND C Registers 
	uint16_t address = ((uint16_t)cpu.state->b << 8) | cpu.state->c;

	// SYS CALL PRINT_B
	if(cpu.state->a ==(uint8_t)1){
		cout << "System call PRINT_B" << endl;
		cout << "Value of Register B: " << (int)cpu.state->b << endl;
		return (uint64_t)10;
	}
	//SYS CALL PRINT_MEM
	else if(cpu.state->a == (uint8_t)2){
		cout << "System call PRINT_MEM" << endl;
		cout << "Address of Register BC: "<< (int)cpu.memory->at(address) << endl;
		return (uint64_t)10;
	}
	//SYS CALL READ_B
	else if(cpu.state->a == (uint8_t)3){
		cout << "System call READ_B" << endl;
		cout << "Please enter an integer" << endl;
		int inputInt;
		cin >> inputInt;
		cpu.state->b = (uint8_t)inputInt;
		cin.clear();
		return (uint64_t)10;
	}
	//SYS CALL READ_MEM
	else if(cpu.state->a == (uint8_t)4){
		cout << "System call READ_MEM" << endl;
		cout << "Please enter an integer" << endl;
		int inputInt;
		cin >> inputInt;
		cin.clear();
		cpu.memory->at(address) = (uint8_t)inputInt;
		return (uint64_t)10;
	}
	//SYS CALL PRINT_STR
	else if(cpu.state->a == (uint8_t)5){
		cout << "System call PRINT_STR" << endl;
		uint16_t i = address;
		while(cpu.memory->at(i)!=(uint8_t)0){ //'\0' 
			cout << (char)(cpu.memory->at(i));
			++i;
		}
		cout << endl;
		return (uint64_t)100;
	}
	//SYS CALL READ_STR
	else if(cpu.state->a == (uint8_t)6){
		cout << "System call READ_STR" << endl;
		cout << "Please enter a string" << endl;
		std::string inputStr = "";
		cin.ignore();
		getline(cin, inputStr);
		uint16_t i;
		for(i=0; i<inputStr.length(); ++i){
			cpu.memory->at(address+i) = inputStr[i];
		}
		//Null-terminated String
		cpu.memory->at(address+i) =(uint8_t)'\0';
		cin.clear();
		return (uint64_t)100;
	}
	//SYS_CALL GET_RND
	else if(cpu.state->a == (uint8_t)7){
		cout << "System call GET_RND" << endl;
		int randNumber;
		srand(time(NULL));
		randNumber = rand();
		cpu.state->b = (uint8_t)randNumber;
		return (uint64_t)100;
	}
	//SYS_CALL TCreate
	else if(cpu.state->a == (uint8_t)11){
		int cycleReturn = 0;
		cout << "System call TCreate" << endl;
		//Main Thread
		//Thread numbers start from 1000 and new threads are generated as plus 1 of last created thread
		currentThread.state = *cpu.state;
		currentThread.threadState = THREAD_RUNNING;
		currentThread.threadID = THREAD_ID_START + totalCreatedThreads;
		currentThread.startingCycle = 0;
		currentThread.totalCycles = cycleCount;

		++totalCreatedThreads;
		currentThread.state.b = THREAD_ID_START + totalCreatedThreads;
		currentThread.waitID = THREAD_ID_START + totalCreatedThreads;
		
		//New Thread
		threadTable newTable;
		newTable.threadID = THREAD_ID_START + totalCreatedThreads;
		newTable.state = *cpu.state;
		newTable.threadState = THREAD_READY;
		newTable.state.pc = address;
		newTable.startingAddress = address;
		newTable.startingCycle = cycleCount;
		newTable.totalCycles = 0;
		newTable.availableSpace = MAX_STACK;
		threadTables.push(newTable);
		return (uint64_t)80;
	}
	//SYS_CALL TExit
	else if(cpu.state->a == (uint8_t)8){
		cout << "System call TExit" << endl;
		threadTable temp;
		setCurrentState(THREAD_TERMINATED); 
		cpu.state->b = EXIT_SUCCESSFUL;
		//Unblocking threads that are waiting.
		for(int i=0; i<threadTables.size(); ++i){
			temp = threadTables.front();
			threadTables.pop();
			if(temp.threadState == THREAD_BLOCKED && temp.waitID == currentThread.threadID){
 				temp.threadState = THREAD_READY;
			}

			threadTables.push(temp);
		}

		return (uint64_t)50;
	}
	//SYS_CALL TJoin
	else if(cpu.state->a == (uint8_t)9){
		cout << "System call TJoin" << endl;
		currentThread.threadState = THREAD_BLOCKED;
		return (uint64_t)40;
		
	}
	//SYS_CALL TYield
	else if(cpu.state->a == (uint8_t)10){
		cout << "System call TYield" << endl;
		setCurrentState(THREAD_READY);
		
		return (uint64_t)40;
	}
	else{
		cout <<  "Unimplemented OS call";
		throw -1;
	}

	return 0;
}

void GTUOS::memToFile(const CPU8080 &cpu){
	FILE *outp;

	outp = fopen("exe.mem" , "w");	 //Opening the file
	if(outp == NULL){ // Checking if file is opened.
		fprintf(stderr, "Couldn't open the file\n");
		exit(1);
	}	
	// Writing memory to file.
	for(uint32_t i=0x0; i < 0x10000; i += 0x00010){
		fprintf(outp, "%.4x:	", i);
		for(uint16_t j = 0x00000; j < 0x00010; ++j){
			fprintf(outp, "%.2x ", cpu.memory->at(i+j));
		}
		fprintf(outp, "\n");
	}


	fclose(outp); //Closing the file
	return;
}

void GTUOS::printCPUStatus(const CPU8080 &cpu){
	cout << "Register A: " << "Value: "<< (int)cpu.state->a << endl;
	cout << "Register B: " << "Value: "<< (int)cpu.state->b << endl;
	cout << "Register C: " << "Value: "<< (int)cpu.state->c << endl;
	cout << "Register D: " << "Value: "<< (int)cpu.state->d << endl;
	cout << "Register E: " << "Value: "<< (int)cpu.state->e << endl;
	cout << "Register H: " << "Value: "<< (int)cpu.state->h << endl;
	cout << "Register L: " << "Value: "<< (int)cpu.state->l << endl;
	cout << "Register SP: " << "Value: "<< (int)cpu.state->sp << endl;
	cout << "Register PC: " << "Value: "<< (int)cpu.state->pc << endl;
	//Conditions
	cout << "Condition cy: " << "Value: "<< (int)cpu.state->cc.cy << endl;
	cout << "Condition pad: " << "Value: "<< (int)cpu.state->cc.pad << endl;
	cout << "Condition p: " << "Value: "<< (int)cpu.state->cc.p << endl;
	cout << "Condition pad2: " << "Value: "<< (int)cpu.state->cc.pad2 << endl;
	cout << "Condition ac: " << "Value: "<< (int)cpu.state->cc.ac << endl;
	cout << "Condition pad3: " << "Value: "<< (int)cpu.state->cc.pad3 << endl;
	cout << "Condition z: " << "Value: "<< (int)cpu.state->cc.z << endl;
	cout << "Condition s: " << "Value: "<< (int)cpu.state->cc.s << endl;
	//End of conditions
	cout << "Register INT_ENABLE: " << "Value: "<< (int)cpu.state->int_enable << endl;
}

void GTUOS::printCPUStatus(threadTable & thread){
	cout << "Register A: " << "Value: "<< (int)thread.state.a << endl;
	cout << "Register B: " << "Value: "<< (int)thread.state.b << endl;
	cout << "Register C: " << "Value: "<< (int)thread.state.c << endl;
	cout << "Register D: " << "Value: "<< (int)thread.state.d << endl;
	cout << "Register E: " << "Value: "<< (int)thread.state.e << endl;
	cout << "Register H: " << "Value: "<< (int)thread.state.h << endl;
	cout << "Register L: " << "Value: "<< (int)thread.state.l << endl;
	cout << "Register SP: " << "Value: "<< (int)thread.state.sp << endl;
	cout << "Register PC: " << "Value: "<< (int)thread.state.pc << endl;
	//Conditions
	cout << "Condition cy: " << "Value: "<< (int)thread.state.cc.cy << endl;
	cout << "Condition pad: " << "Value: "<< (int)thread.state.cc.pad << endl;
	cout << "Condition p: " << "Value: "<< (int)thread.state.cc.p << endl;
	cout << "Condition pad2: " << "Value: "<< (int)thread.state.cc.pad2 << endl;
	cout << "Condition ac: " << "Value: "<< (int)thread.state.cc.ac << endl;
	cout << "Condition pad3: " << "Value: "<< (int)thread.state.cc.pad3 << endl;
	cout << "Condition z: " << "Value: "<< (int)thread.state.cc.z << endl;
	cout << "Condition s: " << "Value: "<< (int)thread.state.cc.s << endl;
	//End of conditions
	cout << "Register INT_ENABLE: " << "Value: "<< (int)thread.state.int_enable << endl;
}

void GTUOS::setCurrentState( threadState newState){
	currentThread.threadState = newState;
}

void GTUOS::switchThread(CPU8080 & cpu, int threadCycle, int DEBUG){
	threadTable temp;
	for(int i=0; i<threadTables.size(); ++i){
		temp = threadTables.front();
		threadTables.pop();
		if(temp.threadState == THREAD_READY){
			//Storing current threads information into queue
			currentThread.state = *cpu.state;
			currentThread.totalCycles += threadCycle;

			//If the change is caused by Round Robin, state switches to READY
			if(currentThread.threadState == THREAD_RUNNING)
				currentThread.threadState = THREAD_READY;

			switch(DEBUG){
				case 2:
					cout << "Switching from Thread ID: " << currentThread.threadID;
					cout << " to Thread ID: " << temp.threadID <<endl;
					cout << "Total cycles on previous thread: " << currentThread.totalCycles << endl;
					break;
				case 3:
					printCPUStatus(temp);
					cout << "Thread ID: " << temp.threadID << endl;
					cout << "Starting Cycle: " << temp.startingCycle << endl;
					cout << "Total Cycles: " << temp.totalCycles << endl;
					cout << "Thread State: " << temp.threadState;
					cout << "   0: RUNNING 1: BLOCKED 2: READY 3: TERMINATED" <<endl;
					cout << "Memory Start: " << temp.startingAddress << endl;
					cout << "Available Stack Space: " << temp.availableSpace << endl;
					break;
			}

			threadTables.push(currentThread);
			//Switching to next ready stated thread.
			currentThread = temp;
			currentThread.threadState = THREAD_RUNNING;
			free(cpu.state);
			cpu.state = new State8080(temp.state);
			break;
		}
		else
			threadTables.push(temp);
	}
}

threadTable GTUOS::getCurrentThread(){
	return currentThread;
}

void GTUOS::switchCPUState(CPU8080 & cpu, threadTable newThread){
	cpu.state = &newThread.state;
}	