#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>

#define TRUE 1
#define MIN_CHEF 6
#define MAX_CHEF 50

//Ingredients to make sekerpare.
typedef enum Ingredients{
	eggs,
	flour,
	butter,
	sugar
} Ingredients;

void exitHandler(int empty);
void printEnum(int ing);
void printChefNo(pid_t childPid, int* chefPIDs, int size);
int checkIngredients(int* requiredIng, int* incomingIng);

int exitStatus = 0;

int main(int argc,char *argv[]){
	if(argc < 2 || strtol(argv[1], NULL, 10) < MIN_CHEF || strtol(argv[1], NULL, 10) > MAX_CHEF  ){
		fprintf(stderr, "Usage: ./exe CHEF_NO   PS: Chef no can be minimum 6, maximum 50\n");
		exit(-1);
	}

	pid_t childPid = -1;
	int i;
	int status;
	int ingFirst;
	int ingSecond;
	pid_t pid;
	int chefCount = strtol(argv[1], NULL, 10);
	//Creating an array to store chef's pid inside the shared memory.
	int *chefPID = mmap(NULL, (sizeof(chefPID)*chefCount) , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	//Chefs required ingredients.
	int requiredIngredients[2];
	//Creating an array inside the shared memory for saler and chefs to communicate.
	int *incomingIngredients = mmap(NULL, (sizeof(incomingIngredients)*2) , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	 //Creating a semophore in shared memory.
	 sem_t *ingredientsReady = mmap(NULL, sizeof(*ingredientsReady), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	 if (ingredientsReady == MAP_FAILED) {
		perror("mmap");
		exit(-1);
	  }

	  //Initializing initialLockphore.
	  if ( sem_init(ingredientsReady, 1, 0) < 0) {
		perror("sem_init");
		exit(EXIT_FAILURE);
	 }

	 //Creating a semophore in shared memory.
	 sem_t *dessertReady = mmap(NULL, sizeof(*dessertReady), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	 if (dessertReady == MAP_FAILED) {
		perror("mmap");
		exit(-1);
	  }

	  //Initializing dessertReady semaphore
	  if ( sem_init(dessertReady, 1, 1) < 0) {
		perror("sem_init");
		exit(EXIT_FAILURE);
	 }





	//Exit Signals
	struct sigaction exitStruct; 
	exitStruct.sa_handler= &exitHandler;
	exitStruct.sa_flags = 0;

	if( (sigemptyset(&exitStruct.sa_mask)== -1) || (sigaction(SIGINT, &exitStruct, NULL) == -1 ) || (sigaction(SIGTERM, &exitStruct, NULL) == -1)) {
		perror("Failed to install Signal handlers");
		exit(-1);
	}





	//Creating Chefs.
	for(i = 0; i<chefCount; ++i){
		if(childPid != 0){
			if( (childPid = fork()) == -1){
				printf("Test\n");
				exit(-1);
			}
			if(childPid != 0)
				chefPID[i] = childPid;
		}
	}

	/******** Initializing Chefs *******/
	//Initializing first 6 chefs to have all the combinations covered for ingredients.
	//First Chef
	if(getpid() == chefPID[0]){
		requiredIngredients[0] = eggs;
		requiredIngredients[1] = flour;

	}

	//Second Chef
	if(getpid() == chefPID[1]){
		requiredIngredients[0] = eggs;
		requiredIngredients[1] = butter;

	}

	//Third Chef
	if(getpid() == chefPID[2]){
		requiredIngredients[0] = eggs;
		requiredIngredients[1] = sugar;

	}

	//Fourth Chef
	if(getpid() == chefPID[3]){
		requiredIngredients[0] = flour;
		requiredIngredients[1] = butter;

	}

	//Fifth Chef
	if(getpid() == chefPID[4]){
		requiredIngredients[0] = flour;
		requiredIngredients[1] = sugar;

	}

	//6th Chef
	if(getpid() == chefPID[5]){
		requiredIngredients[0] = butter;
		requiredIngredients[1] = sugar;

	}

	//Initializing rest of the cehfs to random required ingredients.
	for(i = MIN_CHEF; i<chefCount; ++i){
		if( getpid() == chefPID[i] ){
			requiredIngredients[0] = rand()%4;
			requiredIngredients[1] = rand()%4;
		}
	}


	srand(time(NULL));
	//Chefs here.
	if(childPid == 0){
		while(TRUE){
			if(sem_wait(ingredientsReady) < 0)
				_exit(-1);

			if(checkIngredients(requiredIngredients, incomingIngredients) == 1){
				printChefNo(getpid(), chefPID, chefCount);
				fprintf(stderr, " has taken the ");
				printEnum(incomingIngredients[0]);
				fprintf(stderr, " and the ");
				printEnum(incomingIngredients[1]);
				fprintf(stderr, "\n");

				printChefNo(getpid(), chefPID, chefCount);
				fprintf(stderr, " is preparing the dessert\n");

				printChefNo(getpid(), chefPID, chefCount);
				fprintf(stderr, " has delivered the dessert to the wholesaler\n");
				//Ingredients used.
				incomingIngredients[0] = -1;
				incomingIngredients[1] = -1;

				if (sem_post(dessertReady) < 0)
					_exit(-1);

				printChefNo(getpid(), chefPID, chefCount);
				fprintf(stderr, " is waiting for the ");
				printEnum(requiredIngredients[0]);
				fprintf(stderr, " and the ");
				printEnum(requiredIngredients[1]);
				fprintf(stderr, "\n");

		          	}
		          	else{
		          		if (sem_post(ingredientsReady) < 0)
			          		_exit(-1);
		          	}

			if(exitStatus == 1)//Exit
				_exit(1);

		}
	}
	//Wholesaler
	else{
		while(TRUE){
			//Creating 2 random numbers for wholesaler.
			incomingIngredients[0] = rand()%4;
			incomingIngredients[1] = rand()%4;
			while(incomingIngredients[1] == incomingIngredients[0])
				incomingIngredients[1] = rand()%4;

			fprintf(stderr, "Wholesaler delivers ");
			printEnum(incomingIngredients[0]);
			fprintf(stderr, " and ");
			printEnum(incomingIngredients[1]);
			fprintf(stderr, "\n");

			if (sem_post(ingredientsReady) < 0)
			          break;

			fprintf(stderr, "wholesaler is waiting for the dessert\n");

			if(sem_wait(dessertReady))
				break;

			fprintf(stderr, "wholesaleraler has obtained the dessert and left to sell it\n");

			if(exitStatus == 1) {//Exit
				while (pid = waitpid(-1, NULL, 0))
					if (errno == ECHILD)
				      		break;
				break;
			}
		}
		while (pid = waitpid(-1, NULL, 0))
			if (errno == ECHILD)
		      		break;
		//Unmapping shared memory and destroying semaphores.
		if(sem_destroy(ingredientsReady) < 0) {
			perror("sem_destroy failed");
			exit(EXIT_FAILURE);
		}
		if(munmap(ingredientsReady, sizeof(ingredientsReady)) < 0) {
			perror("munmap failed");
			exit(EXIT_FAILURE);
		}
		if(sem_destroy(dessertReady) < 0) {
			perror("sem_destroy failed");
			exit(EXIT_FAILURE);
		}
		if(munmap(dessertReady, sizeof(dessertReady)) < 0) {
			perror("munmap failed");
			exit(EXIT_FAILURE);
		}


		//Unmapping arrays in shared memory
		if(munmap(chefPID, sizeof(chefPID)*chefCount) < 0) {
			perror("munmap failed");
			exit(EXIT_FAILURE);
		}

		if(munmap(incomingIngredients, sizeof(incomingIngredients)*2) < 0) {
			perror("munmap failed");
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "\n");
		return 0;
	}
}

void exitHandler(int empty){
	exitStatus = 1;
}

void printEnum(int ing){
	switch(ing){
		case 0:
			fprintf(stderr, "eggs");
			break;
		case 1:
			fprintf(stderr, "flour");
			break;
		case 2:
			fprintf(stderr, "butter");
			break;
		case 3:
			fprintf(stderr, "sugar");
			break;
		default:
			fprintf(stderr, "Unknown ingredient");
			break;
	}
}

void printChefNo(pid_t childPid, int* chefPIDs, int size){
	int i;
	for(i = 0; i<size; ++i){
		if(childPid == chefPIDs[i]){
			fprintf(stderr, "chef%d", i);
			break;
		}
	}
}

int checkIngredients(int* requiredIng, int* incomingIng){
	if(requiredIng[0] == incomingIng[0] && requiredIng[1] == incomingIng[1] )
		return 1;
	else if(requiredIng[0] == incomingIng[1] && requiredIng[1] == incomingIng[0] )
		return 1;
	else 
		return 0;
}