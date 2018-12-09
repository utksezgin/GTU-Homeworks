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

uint64_t GTUOS::handleCall(const CPU8080 & cpu){
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