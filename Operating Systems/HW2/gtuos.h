#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include <queue>

using std::queue;

#define THREAD_ID_START 1000
#define MEMORY_SPACE 1000
#define MAX_STACK 500
#define EXIT_SUCCESSFUL 1
#define EXIT_FAILED 0



typedef enum threadState{
	THREAD_RUNNING,
	THREAD_BLOCKED,
	THREAD_READY,
	THREAD_TERMINATED,
} threadStates;
 
typedef struct threadTable{
	State8080 state;
	int threadID;
	int waitID;
	int startingCycle;
	int totalCycles;
	threadStates threadState;
	int startingAddress;
	int availableSpace;
}threadTable;

class GTUOS{
	public:
		GTUOS(){totalCreatedThreads = 0; currentThread.totalCycles = 0; currentThread.startingAddress = 0; currentThread.availableSpace = MAX_STACK;}
		//Handles system calls of CPU.
		uint64_t handleCall(CPU8080 & cpu, int cycleCount);
		//Saves memory into file as 16 bytes of Hexadecimal.
		void memToFile(const CPU8080 & cpu);
		//Prints the CPU Status to terminal.
		void printCPUStatus(const CPU8080 & cpu);
		//Prints the Thread Status to terminal.
		void printCPUStatus(threadTable & thread);
		//Returns the thread table of currrently running thread.
		void setCurrentState(threadState newState);
		//Switches to next ready thread.
		void switchThread(CPU8080 & cpu, int threadCycle, int DEBUG);
		//Returns current thread table
		threadTable getCurrentThread();
		//Changes state of the cpu.
		void switchCPUState(CPU8080 & cpu, threadTable newThread);
	private:
		queue<threadTable> threadTables;
		int totalCreatedThreads;
		threadTable currentThread;
};

#endif
