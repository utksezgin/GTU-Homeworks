#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <sys/file.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include "ServerClient.h"

ssize_t r_read(int fd, void *buf, size_t size);
void exitHandler(int empty);
void* providerThread(void* args);
void* clientThread(void* client);
int checkBestProvider(char preference);
void readProviders(char* fileName);
double factorial(int val);
double taylorSeries(int degree, int iterCount);
void lockAllClients();
void lockAllProviders();
void unlockAllClients();
void unlockAllProviders();
void joinAllProviders();
void detachAllProviders();
void joinAllClients();
void detachAllClients();
int establish ( unsigned short portnum);
int getConnection(int s);
int readData (int s, char *buf, int n);
void printer(char* logFile, char* output);
void sendTermSig();

//Global Variables//
provider *providers;
pthread_t *providerIDs; //Provider Thread IDs
pthread_t *clientThreadIDs; //Client Thread IDs
client **providerQ; //Queues for providers
int *qSize; //Number of client inside the queue
int providerCount = 0;
int currentProviderCount;
int exitStatus = 0;
int totalClient = 0;
int isProviderFinished = 0; 
int sd;
int newClientSd;
char buffer;
char readBuffer[BUFFER_SIZE];
char printBuffer[BUFFER_SIZE];
char logFileName[MAX_NAME_SIZE];

//Mutex&Condi Var.
pthread_cond_t *cond;
pthread_cond_t *clientCond;
pthread_mutex_t *mutex;
pthread_mutex_t *clientMutex;


int main(int argc,char *argv[]){
	if(argc<4){
		fprintf(stderr, "Usage: ./homeworkServer 5555 data.dat log.log\n");
		exit(1);
	}
	strcpy(logFileName, argv[3]);
	//Clearing buffer
	sprintf(printBuffer, "Logs kept at %s\n", argv[3]);
	printer(logFileName, printBuffer);
	//Removing old log file
	remove(logFileName);

	//Local variables
	int i, read_byte;
	client newClient;
	readProviders(argv[2]);
	currentProviderCount = providerCount;
	//Exit Signals
	struct sigaction exitStruct; 
	exitStruct.sa_handler= &exitHandler;
	exitStruct.sa_flags = 0;
	if( (sigemptyset(&exitStruct.sa_mask)== -1) || (sigaction(SIGINT, &exitStruct, NULL) == -1 ) || (sigaction(SIGTERM, &exitStruct, NULL) == -1)) {
		perror("Failed to install Signal handlers");
		exit(-1);
	}

	sprintf(printBuffer, "%d provider threads created \n", providerCount);
	printer(logFileName, printBuffer);
	sprintf(printBuffer, "Name\tPerformance\tPrice\tDuration\n");
	printer(logFileName, printBuffer);
	for(i=0; i<providerCount; ++i){
		sprintf(printBuffer, "%s\t\t%d\t%d\t%d\n", providers[i].name, providers[i].performance, providers[i].price, providers[i].duration);
		printer(logFileName, printBuffer);
	}

	//Allocating memory for thread id array, queue array and queue size array
	providerIDs = (pthread_t*) malloc(sizeof(pthread_t)*providerCount);
	clientThreadIDs = (pthread_t*) malloc(sizeof(pthread_t));
	providerQ = (client**) malloc(sizeof(client*)*providerCount);
	for(i=0; i<providerCount; ++i){
		providerQ[i] = (client*) malloc(sizeof(client) * MAX_QUEUE_SIZE);
	}
	qSize = (int*) malloc(sizeof(int)*providerCount);
	//Allocating memory for mutex and condition variables
	mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)*providerCount);
	cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t)*providerCount);
	clientCond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
	clientMutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&clientMutex[0], NULL);
	pthread_cond_init(&clientCond[0], NULL);
	for(i=0; i<providerCount; ++i){
		pthread_mutex_init(&mutex[i], NULL);
		pthread_cond_init(&cond[i], NULL);
		//Creating threads.
		pthread_create(&providerIDs[i], NULL, providerThread, (void*)i);
	}

		//Establishing the connection.
	if( (sd = establish(atoi(argv[1]))) < 0){
		fprintf(stderr, "Establish failed\n");
		sendTermSig();
		//joinAllProviders();
		//detachAllProviders();
		for(i=0; i<providerCount; ++i){
			pthread_mutex_destroy(&mutex[i]);
			 pthread_cond_destroy(&cond[i]);
		}
		for(i=0; i<totalClient; ++i){
			pthread_cond_destroy(&clientCond[i]);
			pthread_mutex_destroy(&clientMutex[i]);
		}
		//Free'ing allocated memory
		free(providers);
		for(i=0; i<providerCount; ++i){
			free(providerQ[i]);
		}
		free(providerQ);
		free(qSize);
		free(clientThreadIDs);
		free(providerIDs);
		free(mutex);
		free(clientMutex);
		free(cond);
		free(clientCond);
		exit(1);
	}
	sprintf(printBuffer, "Server is waiting for connection at port number %s\n", argv[1]);
	printer(logFileName, printBuffer);
	while(TRUE){
		//Waiting for a client to connect.
		if( (newClientSd = (getConnection(sd))) < 0){
			break;
		}
		if( (read_byte = r_read(newClientSd, &readBuffer, sizeof(readBuffer)))  <= 0){
			continue;
		}
		if(currentProviderCount == 0){
			sprintf(readBuffer, "NO PROVIDER IS AVAILABLE");
			write(newClientSd, readBuffer, strlen(readBuffer));
			close(newClientSd);
		}
		else{
			//Parsing the input
			sscanf(readBuffer, "%s %c %d", newClient.name, &newClient.priority, &newClient.degree);
			sprintf(printBuffer, "Client %s (%c %d) connected.\n", newClient.name, newClient.priority, newClient.degree);
			printer(logFileName, printBuffer);
			newClient.socketId = newClientSd;
			newClient.clientNo = totalClient;
			clientCond = (pthread_cond_t *) realloc(clientCond, sizeof(pthread_cond_t)*providerCount * (totalClient+1) );
			clientMutex = (pthread_mutex_t *) realloc(clientMutex, sizeof(pthread_mutex_t)*(totalClient + 1));
			pthread_mutex_init(&clientMutex[totalClient], NULL);
			pthread_cond_init(&clientCond[totalClient], NULL);
			clientThreadIDs = (pthread_t*) realloc(clientThreadIDs, sizeof(pthread_t) * (totalClient + 1) );
			pthread_create(&clientThreadIDs[totalClient], NULL, clientThread, &newClient);
			++totalClient;
		}
		if(exitStatus == 1)
			break;
	}
	sendTermSig();
	joinAllProviders();
	//joinAllClients();
	//Mutex-Condi Clean-up
	for(i=0; i<providerCount; ++i){
		pthread_mutex_destroy(&mutex[i]);
		 pthread_cond_destroy(&cond[i]);
	}
	for(i=0; i<totalClient; ++i){
		pthread_cond_destroy(&clientCond[i]);
		pthread_mutex_destroy(&clientMutex[i]);
	}
	//Free'ing allocated memory
	for(i=0; i<providerCount; ++i){
		free(providerQ[i]);
	}
	free(providerQ);
	free(qSize);
	free(providerIDs);
	free(mutex);
	free(clientMutex);
	free(cond);
	free(clientCond);
	free(providers);
	close(sd);
	sprintf(printBuffer, "Goodbye.\n");
	printer(logFileName, printBuffer);
	return 0;
}
void* providerThread(void* providerNo){
	srand(time(NULL));
	double result = 0.0;
	int waitReturn = 0;
	int taskCount = 0;
	int localProviderNo = (int) providerNo;
	int currentQindex = providers[localProviderNo].qIndex;
	client newClient;
	double timeOfTask = 0.0;
	double totalTime = 0.0;
	struct timespec ts;
	struct timeval begin, start, end, last;
	gettimeofday(&begin,NULL);
	clock_gettime(CLOCK_REALTIME, &ts);
    	ts.tv_sec += providers[localProviderNo].duration;
	while(TRUE){
		pthread_mutex_lock(&mutex[localProviderNo]);
		while( qSize[localProviderNo] == 0){
			fprintf(stderr, "Provider %s waiting for a task\n", providers[localProviderNo].name);
			 waitReturn = pthread_cond_timedwait(&cond[localProviderNo], &mutex[localProviderNo], &ts);
			 if(waitReturn != 0 ){
			 	sprintf(printBuffer, "%s's time is up\n", providers[localProviderNo].name);
			 	printer(logFileName, printBuffer);
			 	providers[localProviderNo].isFinished = 1;
				providers[localProviderNo].isAvailable = 0;
				pthread_mutex_unlock(&mutex[localProviderNo]);
				--currentProviderCount;
				pthread_exit(NULL);
			 }
		}
		if(exitStatus == 1){
			break;
		}
		gettimeofday(&start,NULL);
		newClient = providerQ[localProviderNo][currentQindex];
		sprintf(printBuffer, "%s is processing task number %d: %d\n", providers[localProviderNo].name, taskCount+1, newClient.degree);
		printer(logFileName, printBuffer);
		result = taylorSeries(newClient.degree, ITERATION_COUNT);
		sleep(rand()%10 + 5);//rand!
		--qSize[localProviderNo];
		providers[localProviderNo].isAvailable = 1;
		currentQindex = (currentQindex+1)%2;
		providers[localProviderNo].qIndex = currentQindex;
		isProviderFinished = 1;
		gettimeofday(&end,NULL);
		timeOfTask = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1000.0;
		sprintf(printBuffer, "%s completed task number %d cos(%d) = %.3lf in %.2f seconds.\n",providers[localProviderNo].name, taskCount, newClient.degree%360,result , timeOfTask);
		printer(logFileName, printBuffer);
		sprintf(readBuffer, "%s’s task completed by %s in %.2lf seconds, cos(%d)=%.3lf, cost is %dTL.", newClient.name, providers[localProviderNo].name, timeOfTask, newClient.degree, result, providers[localProviderNo].price);
		write(newClient.socketId, readBuffer, strlen(readBuffer));
		pthread_cond_broadcast(&clientCond[newClient.clientNo]);
		pthread_mutex_unlock(&mutex[localProviderNo]);
		++taskCount;
		gettimeofday(&last,NULL);
		if(last.tv_sec - begin.tv_sec >= providers[localProviderNo].duration){
			sprintf(printBuffer, "%s's time is up\n", providers[localProviderNo].name);
		 	printer(logFileName, printBuffer);
		 	providers[localProviderNo].isFinished = 1;
			providers[localProviderNo].isAvailable = 0;
			pthread_mutex_unlock(&mutex[localProviderNo]);
			--currentProviderCount;
			pthread_exit(NULL);
		}
		if(exitStatus == 1)
			break;
		

	}
	providers[localProviderNo].isFinished = 1;
	providers[localProviderNo].isAvailable = 0;
	--currentProviderCount;
	pthread_exit(NULL);
}

void* clientThread(void* currClient){
	int bestProvider = 0;
	client newClient = *(client*)currClient;

	bestProvider = checkBestProvider(newClient.priority);
	if(bestProvider == -1){
		fprintf(stderr, "There's no available provider\n");
		pthread_exit(NULL);
	}
	lockAllProviders();
	fprintf(stderr, "%s is forwarded to provider %s\n",newClient.name, providers[bestProvider].name);
	providerQ[bestProvider][ (providers[bestProvider].qIndex)] = newClient;
	++qSize[bestProvider];
	if(qSize[bestProvider] == 2){
		providers[bestProvider].isAvailable = 0;
	}
	pthread_cond_broadcast(&cond[bestProvider]);
	unlockAllProviders();

	pthread_mutex_lock(&clientMutex[newClient.clientNo]);
	while(isProviderFinished == 0 && exitStatus == 0){
		sprintf(printBuffer,"Waiting for %s to finish the task\n", providers[bestProvider].name);
		//printer(logFileName, printBuffer);
		pthread_cond_wait(&clientCond[newClient.clientNo], &clientMutex[newClient.clientNo]);
	}
	if(exitStatus == 1){
		sprintf(readBuffer, "SERVER SHUTDOWN\n\0");
		write(newClient.socketId, readBuffer, strlen(readBuffer));
		pthread_mutex_unlock(&clientMutex[newClient.clientNo]);
		close(newClient.socketId);
		pthread_exit(NULL);
	}
	isProviderFinished = 0;
	close(newClient.socketId);
	pthread_mutex_unlock(&clientMutex[newClient.clientNo]);
	pthread_exit(NULL);
}
void exitHandler(int empty){
	exitStatus = 1;
}

//Returns the index of the best provider available for the client. If the best one is busy(2 in queue) Gives the second available.
//Q Performance
//C Price
//T Time
int checkBestProvider(char preference){ 
	int i;
	int best = 0;
	lockAllProviders();
	while(providers[best].isAvailable == 0 || providers[best].isFinished == 1){
		++best;
	}
	switch (preference){
		case 'Q':
		case 'q':
			for(i=best+1; i<providerCount-1; ++i){
				if(providers[best].performance < providers[i].performance && providers[i].isAvailable == 1  && providers[best].isFinished != 1)
					best = i;
			}
			break;
		case 'C':
		case 'c':
			for(i=1; i<providerCount-1; ++i){
				if(providers[best].price > providers[i].price && providers[i].isAvailable == 1  && providers[best].isFinished != 1)
					best = i;
			}
			break;
		case 'T':
		case 't':
			for(i=1; i<providerCount-1; ++i){
				if(qSize[best] > qSize[i] && providers[i].isAvailable == 1  && providers[best].isFinished != 1)
					best = i;
			}
			break;
		default:
			fprintf(stderr, "Unknown preference.\n");
			best = -1;
	}
	if(best == 0 && providers[best].isAvailable == 1  && providers[best].isFinished != 1 ){
		unlockAllProviders();
		return best;
	}
	else if(providers[best].isAvailable == 1  && providers[best].isFinished != 1){
		unlockAllProviders();
		return best;
	}
	else{
		unlockAllProviders();
		return -1;
	}
}

//Reading providers
void readProviders(char* fileName){
	int read_byte, fd;
	mode_t mode = S_IRUSR | S_IRGRP | S_IROTH;
	char stringToInt[20] = "\0";
	if((fd = open(fileName ,O_RDONLY, mode)) == -1) {
		perror("Failed to open input file");
		exit(-1);
	}

	/**********************************/
	//Reading providers from input file.
	/**********************************/

	providers = (provider*) malloc(sizeof(provider));

	//Skipping first line of the input file
	while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
	while(buffer != '\n'){
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
	}
	//Skipping '\n'
	while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

	while(TRUE){
		providers[providerCount].name[0] = '\0';//Initializing name of the provider as an empty string.,
		//Reading name
		while(buffer != ' '){
			strcat(providers[providerCount].name, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}

		//Skipping ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Reading Performance
		while( buffer!=' '){
			strcat(stringToInt, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		providers[providerCount].performance = atoi(stringToInt);
		stringToInt[0] = '\0';

		//Skipping ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Reading price
		while( buffer!=' '){
			strcat(stringToInt, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		providers[providerCount].price = atoi(stringToInt);
		stringToInt[0] = '\0';

		//Skipping ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Reading Duration
		while( buffer!='\n'){
			strcat(stringToInt, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
			if(read_byte == 0){//EOF
				break;
			}
		}
		providers[providerCount].duration = atoi(stringToInt);
		stringToInt[0] = '\0';
		providers[providerCount].isAvailable = 1;
		providers[providerCount].qIndex = 0;
		providers[providerCount].providerNo = providerCount;
		providers[providerCount].isFinished = 0;
		++providerCount;

		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		if(read_byte == 0){//EOF
			break;
		}

		providers = (provider*) realloc(providers, sizeof(provider)*(providerCount+1));

	}
	close(fd);
}

double taylorSeries(int degree, int iterCount){
	if(degree<0)
		degree*=-1;
	int i;
	double result = 0.0;
	double degreeToRadian = (M_PI * (double) (degree%360) / 180.0) ;
	int sign = 1;
	for(i=0; i<iterCount; ++i){
		result += ( sign* pow(degreeToRadian, 2*i) / factorial(2*i));
		sign *=-1;
	}

	return result;

}

double factorial(int val){
	int i;
	int returnVal = 1;
	for(i=1; i<=val;++i){
		returnVal *= i;
	}
	return (double)returnVal;
}

void lockAllClients(){
	int i;
	for(i=0; i<totalClient; ++i){
		pthread_mutex_lock(&clientMutex[i]);
	}
}

void unlockAllClients(){
	int i;
	for(i=0; i<providerCount; ++i){
		pthread_mutex_unlock(&clientMutex[i]);
	}
}

void lockAllProviders(){
	int i;
	for(i=0; i<providerCount; ++i){
		pthread_mutex_lock(&mutex[i]);
	}
}

void unlockAllProviders(){
	int i;
	for(i=0; i<providerCount; ++i){
		pthread_mutex_unlock(&mutex[i]);
	}
}

void joinAllProviders(){
	int i;
	sprintf(readBuffer, "Terminating providers.\n");
	printer(logFileName, readBuffer);
	for(i=0; i<providerCount; ++i){
		pthread_join(providerIDs[i], NULL);
	}
}
void joinAllClients(){
	int i;
	sprintf(readBuffer, "Terminating clients.\n");
	printer(logFileName, readBuffer);
	for(i=0; i<totalClient; ++i){
		pthread_join(clientThreadIDs[i], NULL);
	}
}
void detachAllProviders(){
	int i;
	for(i=0; i<providerCount; ++i){
		pthread_detach(providerIDs[i]);
	}
}
void detachAllClients(){
	int i;
	for(i=0; i<totalClient; ++i)
		pthread_detach(clientThreadIDs[i]);
}

//From out book that was mentioned on the last slide
int getConnection(int s){
    int t; /* socket of connection */
    if ((t = accept(s,NULL,NULL)) < 0) /* accept connection if there is one */
        return(-1);
    return(t);
}

//From out book that was mentioned on the last slide
int establish ( unsigned short portnum){
    char myname[MAX_CONNECTION+1];
    int s;
    struct sockaddr_in sa;
    struct hostent *hp;
    
    memset(&sa, 0, sizeof(struct sockaddr_in)); /* clear our address */
    gethostname(myname, MAX_NAME_SIZE); /* who are we? */
    hp= gethostbyname(myname); /* get our address info */
    

    if (hp == NULL) {
        fprintf(stderr,"HP null\n");
        return(-1);
    }
    sa.sin_family= hp->h_addrtype; /* this is our host address */
    sa.sin_port= htons(portnum); /* this is our port number */
    if ((s= socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Socket error\n" );
        return(-1);
    }
    if (bind(s,(struct sockaddr *)&sa,sizeof(struct sockaddr_in)) < 0) {
        perror("bind error " );
        close(s);
        return(-1); /* bind address to socket */
    }
    listen(s, MAX_CONNECTION); /* max # of queued connects */
    return(s);
}

int readData (int s, /* connected socket */
		char *buf, /* pointer to the buffer */
		int n /* number of characters (bytes) we want */ )
		{
	int bcount; /* counts bytes read */
	int br; /* bytes read this pass */
	bcount= 0;
	br= 0;
	while (bcount < n) { /* loop until full buffer */
		if ((br= read(s,buf,n-bcount)) > 0) {
			bcount += br; /* increment byte counter */
			buf += br; /* move buffer ptr for next read */
		}
		else if (br < 0) /* signal an error to the caller */
			return(-1);
	}
	return(bcount);
}

void printer(char* logFile, char* output){
	int logfd;
	mode_t mode = S_IRWXU;

	if((logfd = open(logFile, O_CREAT  | O_APPEND  | O_RDWR, mode)) == -1) {
		perror("Failed to open input file");
		exit(1);
	}

	fprintf(stderr, "%s", output);
	while(write(logfd, output, strlen(output)) == -1 && errno == EINTR);

	close(logfd);
}

void sendTermSig(){
	int i;
	sprintf(printBuffer, "Termination signal received.\n");
	printer(logFileName, printBuffer);

	exitStatus = 1;
	for(i=0; i<providerCount; ++i){
		qSize[i] = -1;
		pthread_cond_broadcast(&cond[i]);
	}
	for(i=0; i<totalClient;++i){
		isProviderFinished = -1;
		pthread_cond_broadcast(&clientCond[i]);
	}
}