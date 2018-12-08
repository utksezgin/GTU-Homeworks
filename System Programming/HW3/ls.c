#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>

void printMode(mode_t mode);
void exitHandler(int signal);

DIR *currentDir;

int main(int argc,char *argv[]){
	struct dirent *currentDirStruct;
	struct stat *fileStat;

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	fprintf(stderr, "cwd from ls: %s", cwd);
	//Exit Signals
	struct sigaction exitStruct; 
	exitStruct.sa_handler= &exitHandler;
	exitStruct.sa_flags = 0;

	if( (sigemptyset(&exitStruct.sa_mask)== -1) || (sigaction(SIGINT, &exitStruct, NULL) == -1 ) || (sigaction(SIGTERM, &exitStruct, NULL) == -1)) {
		perror("Failed to install Signal handlers");
		exit(-1);
	}


	if((currentDir = opendir(cwd) ) == NULL){
		perror("Couldn't open the directory.\n");
		exit(-1);
	}
	else{
		fprintf(stderr, "File Name\tAccess Rights\tFile Size\n");
		while( (currentDirStruct = readdir(currentDir)) != NULL ){
			if( strcmp(currentDirStruct->d_name, ".." ) == 0 ||  strcmp(currentDirStruct->d_name, "." ) == 0 || strcmp(currentDirStruct->d_name, "~" ) == 0 )
				continue;

			if(stat(currentDirStruct->d_name, fileStat) < 0)
				perror("Failed to get stat for the file");

			fprintf(stderr, "%s\t", currentDirStruct->d_name);
			printMode(fileStat->st_mode);

			
			fprintf(stderr, "%zu\n", fileStat->st_size);
		}
	}

	closedir(currentDir);
	return 0;
}

void printMode(mode_t mode){
	fprintf(stderr, (S_ISDIR(mode) ? "d" : "-"));
	fprintf(stderr, (mode & S_IRUSR) ? "r" : "-");
	fprintf(stderr, (mode & S_IWUSR) ? "w" : "-");
	fprintf(stderr, (mode & S_IXUSR) ? "x" : "-");
	fprintf(stderr, (mode & S_IRGRP) ? "r" : "-");
	fprintf(stderr, (mode & S_IWGRP) ? "w" : "-");
	fprintf(stderr, (mode & S_IXGRP) ? "x" : "-");
	fprintf(stderr, (mode & S_IROTH) ? "r" : "-");
	fprintf(stderr, (mode & S_IWOTH) ? "w" : "-");
	fprintf(stderr, (mode & S_IXOTH) ? "x" : "-");
	fprintf(stderr, "\t");
}

void exitHandler(int fileD){
	closedir(currentDir);
	exit(1);
}