#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define TRUE 1

ssize_t r_read(int fd, void *buf, size_t size);
void exitHandler(int fileD);

int fd;

int main(int argc,char *argv[]){
	if(argc<2){	
		fprintf(stderr, "Unknown number of inputs.\n");
		exit(-1);
	}

	mode_t mode = S_IRUSR | S_IRGRP | S_IROTH;
	int read_byte;
	char buffer;
	int lineCount = 0;

	//Exit Signals
	struct sigaction exitStruct; 
	exitStruct.sa_handler= &exitHandler;
	exitStruct.sa_flags = 0;

	if( (sigemptyset(&exitStruct.sa_mask)== -1) || (sigaction(SIGINT, &exitStruct, NULL) == -1 ) || (sigaction(SIGTERM, &exitStruct, NULL) == -1)) {
		perror("Failed to install Signal handlers");
		exit(-1);
	}

	//Opening the data file.
	if((fd = open(argv[1] ,O_RDONLY, mode)) == -1) {
		perror("Failed to open input file");
		exit(-1);
	}

	while(TRUE){
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		if(read_byte == 0){
			close(fd);
			break;
		}
		if(buffer == '\n')
			++lineCount;
	}

	fprintf(stderr, "Line Count for %s: %d\n", argv[1], lineCount+1);

}

ssize_t r_read(int fd, void *buf, size_t size) {
    ssize_t retval;
    while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
    return retval;
}

void exitHandler(int fileD){
	close(fd);
	close(fileD);
	exit(1);
}