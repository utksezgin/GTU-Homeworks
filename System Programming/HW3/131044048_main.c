#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define TRUE 1
#define MAX_SIZE 1024

void help();
void pwd();
void cd();
void exitHandler(int signal);

char currDirName[MAX_SIZE];
int exitStatus = 0; //Stays as 0 untill exit command.

int main(int argc,char *argv[]){
	//USAGE
	pid_t childPid;
	int status;
	char ls[MAX_SIZE];
	char cat[MAX_SIZE];
	char wc[MAX_SIZE];
	char currPath[MAX_SIZE];
	char shellInput[MAX_SIZE];
	char fileName[MAX_SIZE];
	int i, j;

	//Exit Signals
	struct sigaction exitStruct; 
	exitStruct.sa_handler= &exitHandler;
	exitStruct.sa_flags = 0;

	if( (sigemptyset(&exitStruct.sa_mask)== -1) || (sigaction(SIGINT, &exitStruct, NULL) == -1 ) || (sigaction(SIGTERM, &exitStruct, NULL) == -1)) {
		perror("Failed to install Signal handlers");
		exit(-1);
	}

	getcwd(currPath, MAX_SIZE);

	memset(&ls[0], 0, sizeof(ls));
	memset(&cat[0], 0, sizeof(cat));
	memset(&wc[0], 0, sizeof(wc));

	strcat(ls, currPath);
	strcat(ls, "/ls");
	strcat(cat, currPath);
	strcat(cat, "/cat");
	strcat(wc, currPath);
	strcat(wc, "/wc");

	while(TRUE){
		memset(&shellInput[0], 0, sizeof(shellInput));
		memset(&fileName[0], 0, sizeof(fileName));
		fgets(shellInput, MAX_SIZE, stdin);


		//ls
		if(shellInput[0] == 'l' && shellInput[1] == 's'){
			if( (childPid = fork()) == -1 )
				exit(-1);	
			else if(childPid == 0){
				execv(ls, NULL);
				_exit(1);
			}
			else{
				waitpid(childPid, &status, 0);
			}
		}
		//pwd
		else if(shellInput[0] == 'p' && shellInput[1] == 'w' && shellInput[2] == 'd'){
			pwd();
		}
		//cd
		else if(shellInput[0] == 'c' && shellInput[1] == 'd'){
			j=0;
			for(i=2; shellInput[i] != '\n'; ++i){
				if(shellInput[i] != ' ' && shellInput[i] != '\n'){
					fileName[j] = shellInput[i];
					++j;
				}
			}
			cd(fileName);
		}
		//help
		else if(shellInput[0] == 'h' && shellInput[1] == 'e' && shellInput[2] == 'l' && shellInput[3] == 'p'){
			help();
		}
		//cat
		else if(shellInput[0] == 'c' && shellInput[1] == 'a' && shellInput[2] == 't'){
			j=0;
			for(i=3; shellInput[i] != '\n'; ++i){
				if(shellInput[i] != ' ' && shellInput[i] != '\n'){
					fileName[j] = shellInput[i];
					++j;
				}
			}
			if( (childPid = fork()) == -1 )
				exit(-1);	
			else if(childPid == 0){
				if(execv(cat, (char*[]){cat, fileName, NULL} ) == -1)
					perror("Failed to execv");
				_exit(1);
			}
			else{
				waitpid(childPid, &status, 0);
			}
		}
		//wc
		else if(shellInput[0] == 'w'  && shellInput[1] == 'c' ){
			j=0;
			for(i=2; shellInput[i] != '\n'; ++i){
				if(shellInput[i] != ' ' && shellInput[i] != '\n'){
					fileName[j] = shellInput[i];
					++j;
				}
			}
			if( (childPid = fork()) == -1 )
				exit(-1);	
			else if(childPid == 0){
				if(execv(wc, (char*[]){wc, fileName, NULL} ) == -1)
					perror("Failed to execv");
				_exit(1);
			}
			else{
				waitpid(childPid, &status, 0);
			}
		}
		//exit
		else if(shellInput[0] == 'e' && shellInput[1] == 'x' && shellInput[2] == 'i' && shellInput[3] == 't' ){
			exitStatus = 1;
		}



		if(exitStatus == 1 || exitStatus == -1)
			break;
	}
	if(exitStatus == -1)
		fprintf(stderr, "Terminate signal received, exiting the program.\n");
	else
		fprintf(stderr, "Exited the program successfully.\n");

	return 0;
}


void help(){
	fprintf(stderr, "\n\n-------------------------------------------------\n");
	fprintf(stderr, "ls:  Lists file type, access rights, size and name of all files in the present working\n");
	fprintf(stderr, "presentwd: Prints the present working directory\n");
	fprintf(stderr, "cd: Changes the present working directory to location provided as argument\n");
	fprintf(stderr, "help: Prints the list of supported commands\n");
	fprintf(stderr, "cat: Prints on standart output the contents of the file provided to it as argument\n");
	fprintf(stderr, "wc: Print on standart output the number of lines in the file provided to it as argument\n");
	fprintf(stderr, "exit: Exits the shell\n");
	fprintf(stderr, "-------------------------------------------------\n\n");
}

void pwd(){
	fprintf(stderr, "%s\n", getcwd(currDirName, sizeof(currDirName)));
}

void cd(const char* newDir){
	int cdReturn;

	if( (cdReturn = chdir(newDir)) == -1 ){
		perror("Failed to change directory.");
	}

}

void exitHandler(int fileD){
	wait(NULL);
	exitStatus = -1;
}