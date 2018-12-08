#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <complex.h>
#include <math.h>

/* Defines */
#define N atoi(argv[2])
#define M atoi(argv[6])
#define X argv[4]
#define PROCESSLOG "process.log"


void exitHandler(int fileD);
void fullHandler(int fileD);
void emptyHandler(int fileD);
ssize_t r_read(int fd, void *buf, size_t size);
void dftPrint(double *sequence, int size);

//File Descriptor vars.
int fd, fdLog;

//TODO: LOGFILE
int main(int argc,char *argv[]){
	if(argc<7){
		fprintf(stderr, "Usage: ./multiprocess_DFT -N 5 -X file.dat -M 100");
		exit(1);
	}
	
	pid_t childPid;
	int status = 0;
	int i, j;

	double numSequence[N];
	char stringBuffer[N*3];
	char newLine[1] = "\n";

	int read_byte = 0;
	int readCount = 0;
	int lineCount = 0;

	struct stat fileStats; //Used to store file size via fstat function.
	struct sigaction exitStruct; //Action handler.
	struct sigaction fileFullAct, fileEmptyAct;
	sigset_t fileNotAvailableMask, processDoneMask;
	size_t fileSize;
	
	mode_t mode = S_IRWXU;
	sigset_t exitMask;
	//int fd, fdLog;
	
	//Signal Mask
	sigfillset(&processDoneMask);
	sigdelset(&processDoneMask, SIGUSR1);
	sigdelset(&processDoneMask, SIGINT);
	sigfillset(&fileNotAvailableMask);
	sigdelset(&fileNotAvailableMask, SIGUSR2);
	sigdelset(&fileNotAvailableMask, SIGINT);

	remove(X); //Deleting the old file. 
	remove(PROCESSLOG);

	//Exit Signal handler
	memset(&exitStruct, 0, sizeof(exitStruct));
	exitStruct.sa_handler = &exitHandler;
	exitStruct.sa_flags = 0;
	sigaction(SIGINT, &exitStruct, NULL);
	//Full File Handler
	memset(&fileFullAct, 0, sizeof(fileFullAct));
	fileFullAct.sa_handler = &fullHandler;
	fileFullAct.sa_flags = 0;	
	sigaction(SIGUSR2, &fileFullAct, NULL);
	//Empty File Handler
	memset(&fileEmptyAct, 0, sizeof(fileEmptyAct));
	fileEmptyAct.sa_handler = &emptyHandler;
	fileEmptyAct.sa_flags = 0;
	sigaction(SIGUSR1, &fileEmptyAct, NULL);
	
	//Opening the data file.
	if((fd = open(X, O_CREAT  | O_APPEND  | O_RDWR, mode)) == -1) {
		perror("Failed to open input file");
		exit(1);
	}
	//Opening the log file.
	if((fdLog = open(PROCESSLOG, O_CREAT  | O_APPEND  | O_RDWR, mode)) == -1) {
	perror("Failed to open input file");
	exit(1);
}

	if(sigemptyset(&exitMask) == -1 || (sigaddset(&exitMask, SIGINT))){
		perror("Failed to initialize the exit signal mask");
		close(fd);
		close(fdLog);
		_exit(EXIT_FAILURE);
	}

	if(sigprocmask(SIG_BLOCK, &processDoneMask, NULL) == -1){
		perror("Failed to block signal\n");
		close(fd);
		close(fdLog);
		_exit(EXIT_FAILURE);
	}

	if(sigprocmask(SIG_BLOCK, &exitMask, NULL) == -1){
		perror("Failed to block the signal.");
		close(fd);
		close(fdLog);
		_exit(EXIT_FAILURE);
	}

	if(sigprocmask(SIG_BLOCK, &fileNotAvailableMask, NULL) == -1){
		perror("Failed to block signal\n");
		close(fd);
		close(fdLog);
		_exit(EXIT_FAILURE);
	}

	if( (childPid = fork() ) == -1 ){
		perror("Fork failed");
		close(fd);
		close(fdLog);
		exit(-1);
	}
	else if(childPid == 0){//Child - Process B	

		for( ; ; ){
			//sleep(1);
			flock(fd, LOCK_EX);
			dprintf(fdLog, "Process B locking the file.\n"); //Writing to a log file.
			fstat(fd, &fileStats);
			lineCount = fileStats.st_size/sizeof(numSequence);
			if(lineCount != 1){
				lseek(fd, (lineCount-1)*sizeof(numSequence) ,SEEK_SET);
			}
			else
				lseek(fd, 0, SEEK_SET);

			if(lineCount !=0){
				while( (read_byte = r_read(fd, numSequence, sizeof(numSequence))) == -1 && (errno == EINTR));
				if(read_byte == 0){
					fprintf(stderr, "failed\n");
					close(fd);
					close(fdLog);
					_exit(EXIT_FAILURE);
				}

				fprintf(stderr, "Process B: the dft of line %d ( ", lineCount);
				dprintf(fdLog, "Process B: the dft of line %d ( ", lineCount); 
				for(i = 0 ; i< N; ++i){
					fprintf(stderr, "%.1f ", numSequence[i]);
					dprintf(fdLog, "%.1f ", numSequence[i]);
				}

				fprintf(stderr, ") is: ");
				dprintf(fdLog, ") is: ");

				dftPrint(numSequence, N);
				fprintf(stderr, "\n");
				dprintf(fdLog, "\n");
				//Deleting the last line.
				fstat(fd, &fileStats);
				lineCount = fileStats.st_size/sizeof(numSequence);

				if( lineCount != 0)
					if(ftruncate(fd, (lineCount-1)* sizeof(numSequence)) == -1 ){
						perror("Failed to execute ftruncate");
						close(fd);
						close(fdLog);
						_exit(EXIT_FAILURE);
					}
			}

			flock(fd, LOCK_UN);
			dprintf(fdLog, "Process B unlocking the file.\n"); 

			if(sigprocmask(SIG_UNBLOCK, &exitMask, NULL) == -1){
				perror("Failed to unblock the signal.");
				close(fd);
				close(fdLog);
				exit(EXIT_FAILURE);
			}
		}
		
		close(fd);
		close(fdLog);
		_exit(EXIT_SUCCESS);
	}
	else{//Parent - Process A
		for( ; ; ){
			flock(fd, LOCK_EX);
			dprintf(fdLog, "Process A locking the file.\n");
			
			for(i=0; i<N; ++i){
				numSequence[i] = ( (double)( rand()%100))/10.0;
			}
			fstat(fd, &fileStats);
			lineCount = fileStats.st_size/sizeof(numSequence);
			if(lineCount <=M){
				fstat(fd, &fileStats);
				lineCount = fileStats.st_size/sizeof(numSequence);
				fprintf(stderr, "Process A: I’m producing a random sequence for line %d: ", lineCount);
				dprintf(fdLog, "Process A: I’m producing a random sequence for line %d: ", lineCount);
				
				for(i=0; i<N; ++i){
					fprintf(stderr, "%.1f ", numSequence[i]);
					dprintf(fdLog, "%.1f ", numSequence[i]);
				}
				fprintf(stderr, "\n");
				dprintf(fdLog, "\n");
				while(write(fd, numSequence, sizeof(numSequence)) == -1 && errno == EINTR);

				fstat(fd, &fileStats);
				lineCount = fileStats.st_size/sizeof(numSequence);
				
				//Sending signal. if the file was empty, it's not anymore.
				/*if( kill(childPid, SIGUSR1) == -1){
					perror("Failed to send signal to process A.\n");
					_exit(EXIT_FAILURE);
				}
				else
					fprintf(stderr, "Parent sending signal to: %d\n", childPid);*/

				flock(fd, LOCK_UN);
				dprintf(fdLog, "Process A unlocking the file.\n"); 
				if(sigprocmask(SIG_UNBLOCK, &exitMask, NULL) == -1){
					perror("Failed to unblock the signal.");
					close(fd);
					close(fdLog);
					exit(EXIT_FAILURE);
				}
			}	
		}
		wait(&status);
		close(fdLog);
		close(fd);
	}
	close(fdLog);
	close(fd);
	return 0;
}

//From the last year's book.
ssize_t r_read(int fd, void *buf, size_t size) {
    ssize_t retval;
    while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
    return retval;
}

void dftPrint(double *sequence, int size){
	double complex num = 0.0 + 0.0 * I;
	int i, j;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j)
		if(i != j){
			num += sequence[j]*(cos( (2*M_PI * i*j ) / (size) )  + sin(  (2*M_PI * i*j ) / (size)  )* I );
		}

		fprintf(stderr, "%.1f + %.1fi ", creal(num), cimag(num));
	}
}

void exitHandler(int fileD){
	int status;
	wait(&status);
	close(fileD);
	close(fdLog);
	_exit(EXIT_SUCCESS);
}

void emptyHandler(int fileD){
	//Empty intentionally.
}
void fullHandler(int fileD){
	//Empty intentionally.
}