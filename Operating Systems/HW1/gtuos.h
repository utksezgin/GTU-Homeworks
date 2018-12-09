#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"


class GTUOS{
	public:
		//Handles system calls of CPU.
		uint64_t handleCall(const CPU8080 & cpu);
		//Saves memory into file as 16 bytes of Hexadecimal.
		void memToFile(const CPU8080 & cpu);
		//Prints the CPU Status to terminal.
		void printCPUStatus(const CPU8080 & cpu);
};

#endif
