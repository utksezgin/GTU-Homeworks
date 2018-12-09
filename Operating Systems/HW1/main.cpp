//Azmi Utku Sezgin 131044048
#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

int main (int argc, char**argv)
{
	if (argc != 3){
		std::cerr << "Usage: prog exeFile debugOption\n";
		exit(1); 
	}
	int DEBUG = atoi(argv[2]);
	int cycleCount = 0;

	memory mem;
	CPU8080 theCPU(&mem);
	GTUOS	theOS;
	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);	
 
	do	
	{
		cycleCount += theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall())
			cycleCount += theOS.handleCall(theCPU);
		//Debug cases
		switch(DEBUG){
			case 0:
				break;
			case 1:
				theOS.printCPUStatus(theCPU);
				break;
			case 2:
				theOS.printCPUStatus(theCPU);
				uint8_t input;
				std::cout << "Waiting for an input to continue" << std::endl;
				std::cin >> input;
				break;
		}	

	}	while (!theCPU.isHalted());
	//Saving memory into exe.mem file.
	//All the debug modes saves the memory.
	theOS.memToFile(theCPU);
	//Printing cycle count of the program.
	std::cout << argv[1] <<" takes " << cycleCount << " cycles to execute." << std::endl;
	return 0;
}

