//Azmi Utku Sezgin 131044048
#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

#define QUANTA 100

int main (int argc, char**argv)
{
	if (argc != 3){
		std::cerr << "Usage: prog exeFile debugOption\n";
		exit(1); 
	}
	int DEBUG = atoi(argv[2]);
	int threadCycle = 0;
	int currentCycle = 0;
	int totalCycle = 0;

	memory mem;
	CPU8080 theCPU(&mem);
	GTUOS	theOS;
	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);	
 
	do	
	{
		currentCycle += theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall())
			currentCycle += theOS.handleCall(theCPU, totalCycle);
		//Debug cases
		switch(DEBUG){
			case 0:
				break;
			case 1:
				theOS.printCPUStatus(theCPU);
				break;
		}
		totalCycle += currentCycle;
		threadCycle += currentCycle;
		currentCycle = 0;
		threadTable currentThread = theOS.getCurrentThread();
		if( (threadCycle >= QUANTA) ||  (currentThread.threadState != THREAD_RUNNING)){
			theOS.switchThread(theCPU, threadCycle, DEBUG);
			threadCycle = 0;
		}

	}	while (!theCPU.isHalted());
	//Saving memory into exe.mem file.
	//All the debug modes saves the memory.
	theOS.memToFile(theCPU);
	//Printing cycle count of the program.
	std::cout << argv[1] <<" takes " << totalCycle << " cycles to execute." << std::endl;
	return 0;
}

