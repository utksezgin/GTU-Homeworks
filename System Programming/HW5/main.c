#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define TOTALFLORIST 3
#define TOTALFLOWERS 3

typedef enum flower{
	orchid,
	clove,
	daffodil,
	violet,
	rose,
}flower;

typedef struct location2D{
	int locationX;
	int locationY;
}location2D;

typedef struct florist{
	char name[1024];
	location2D location;
	double speed;
	flower flowers[3];
}florist;

typedef struct flowerOrder{
	char clientName[1024];
	char flowerName[10];
	int flowerNo;
	location2D location;
	int floristNo;
}flowerOrder;

typedef struct floristReturn{
	int numSales;
	int totalTime;
}floristReturn;

pthread_cond_t cond[3] = {PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER}; 
pthread_mutex_t mutex[3] = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};

ssize_t r_read(int fd, void *buf, size_t size);
double euclideanDist(location2D location1, location2D location2);
int flowerToEnum(const char* flower);
void prepareAndDeliverFlower(int time);
int findClosestFlorist(location2D location, flower orderedFlower);
void* floristThread(void* floristNo);

int fd;
int isLastOrder = 0; //If it's 1, threads join to main thread.
char buffer;

florist florists[TOTALFLORIST];
flowerOrder floristOrders[TOTALFLORIST][200]; //3 Different order arrays that will be used by florists as queues.
floristReturn floristReturns[3]; //Parallel array for return values from florists.
int orderSizes[TOTALFLORIST] = {0, 0, 0}; //Parallel array to store sizes of orders.
pthread_t threadIDs[TOTALFLORIST]; //Stores thread IDs


int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr, "Usage: ./exe data.dat");
		exit(1);
	}

	int error;
	int i;
	int read_byte;
	int temp;
	char stringToInt[20] = "\0";
	char tempFlower[10] = "\0";
	mode_t mode = S_IRUSR | S_IRGRP | S_IROTH;
	double distanceReturn = 0.0;
	flowerOrder tempOrder;

	if((fd = open(argv[1] ,O_RDONLY, mode)) == -1) {
		perror("Failed to open input file");
		exit(-1);
	}

	fprintf(stderr, "Processing requests\n");
	//Reading 3 florists from the data.dat
	for(i = 0; i<TOTALFLORIST; ++i){

		florists[i].name[0] = '\0';

		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Reading name
		while(buffer != ' '){
			strcat(florists[i].name, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}

		//Skipping ' ' and '(' characters.
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Reading locationX
		while( buffer!=','){
			strcat(stringToInt, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		florists[i].location.locationX = atoi(stringToInt);
		stringToInt[0] = '\0';
	
		//Skipping  ','
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Reading locationY
		while( buffer!=';'){
			strcat(stringToInt, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		florists[i].location.locationY = atoi(stringToInt);
		stringToInt[0] = '\0';



		//Skipping  ','
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Skipping  ';'
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//
		while( buffer !=')'){
			strcat(stringToInt, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		florists[i].speed = atof(stringToInt);
		stringToInt[0] = '\0';

		//Skipping  ')'
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Skipping  ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Skipping  ';'
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Skipping  ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));


		//First flower
		while( buffer != ','){
			strcat(tempFlower, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		florists[i].flowers[0] = flowerToEnum(tempFlower);
		tempFlower[0] = '\0';
		

		//Skipping  ','
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Skipping  ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Second flower
		while( buffer != ','){
			strcat(tempFlower, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		florists[i].flowers[1] = flowerToEnum(tempFlower);
		tempFlower[0] = '\0';

		//Skipping  ','
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Skipping  ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Third flower
		while( buffer != '\n'){
			strcat(tempFlower, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		florists[i].flowers[2] = flowerToEnum(tempFlower);
		tempFlower[0] = '\0';


	}
	
	//Skipping  '\n'
	while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
	//Skipping  '\n'
	while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

	//Creating threads
	for(i=0; i<TOTALFLORIST; ++i){

		floristReturns[i].numSales = 0;
		floristReturns[i].totalTime = 0;
		if (error = pthread_create(&threadIDs[i], NULL, floristThread, (void*)i))
			 fprintf(stderr, "Failed to create thread: %s\n", strerror(error));
	}
	//Reading orders
	while(TRUE){

		tempOrder.clientName[0] = '\0';
		tempOrder.flowerName[0] = '\0';


		//Reading client name
		while(buffer != ' '){
			strcat(tempOrder.clientName, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}

		//Skipping  ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		if(read_byte == 0){
			fprintf(stderr, "All requests processed\n");
			break;
		}
		//Skipping  '('
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		if(read_byte == 0){
			fprintf(stderr, "All requests processed\n");
			break;
		}

		//Reading locationX
		while( buffer!=','){
			strcat(stringToInt, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		tempOrder.location.locationX = atoi(stringToInt);
		stringToInt[0] = '\0';
	
		//Skipping  ','
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Reading locationY
		while( buffer!=')'){
			strcat(stringToInt, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		tempOrder.location.locationY = atoi(stringToInt);
		stringToInt[0] = '\0';

		//Skipping  ')'
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Skipping  ':'
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		//Skipping  ' '
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));

		//Ordered flower name
		while( buffer != '\n' & read_byte != 0){
			strcat(tempOrder.flowerName, &buffer);
			while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		}
		tempOrder.flowerNo = flowerToEnum(tempOrder.flowerName);
		tempOrder.floristNo = findClosestFlorist(tempOrder.location, tempOrder.flowerNo);

		pthread_mutex_lock(&mutex[2]);
		pthread_mutex_lock(&mutex[1]);
		pthread_mutex_lock(&mutex[0]);

		floristOrders[tempOrder.floristNo][orderSizes[tempOrder.floristNo]] = tempOrder;
		++orderSizes[tempOrder.floristNo];

		pthread_cond_signal(&cond[tempOrder.floristNo]);
		pthread_mutex_unlock(&mutex[0]);
		pthread_mutex_unlock(&mutex[1]);
		pthread_mutex_unlock(&mutex[2]);

		//Skipping  '\n'
		while( (read_byte = r_read(fd, &buffer, sizeof(buffer))) == -1 && (errno == EINTR));
		if(read_byte == 0){
			fprintf(stderr, "All requests processed\n");
			isLastOrder = 1;
		}
	
		if(isLastOrder)
			break;
	}
	//End of Florists parsing.
	pthread_join(threadIDs[0], NULL);
	pthread_join(threadIDs[1], NULL);
	pthread_join(threadIDs[2], NULL);
	pthread_detach(threadIDs[0]);
	pthread_detach(threadIDs[1]);
	pthread_detach(threadIDs[2]);

	fprintf(stderr, "\n\n-------------------------------------------------\n");
	fprintf(stderr, "Florist\t# of sales\tTotal time\n");
	fprintf(stderr, "-------------------------------------------------\n");
	fprintf(stderr, "%s\t%d\t%dms\n", florists[0].name, floristReturns[0].numSales, floristReturns[0].totalTime);
	fprintf(stderr, "%s\t%d\t%dms\n", florists[1].name, floristReturns[1].numSales, floristReturns[1].totalTime);
	fprintf(stderr, "%s\t%d\t%dms\n", florists[2].name, floristReturns[2].numSales, floristReturns[2].totalTime);
	fprintf(stderr, "-------------------------------------------------\n");

	close(fd);

	return 0;
}

//From the last year's book.
ssize_t r_read(int fd, void *buf, size_t size) {
    ssize_t retval;
    while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
    return retval;
}

double euclideanDist(location2D location1, location2D location2){
	return( sqrt( pow( (double)(location1.locationX-location2.locationX), 2.0 ) + pow( (double) (location1.locationY-location2.locationY), 2.0) ) );
}

int findClosestFlorist(location2D location, flower orderedFlower){
	double closestF = 100000.0; //Initial value, must be higher than the first calculated distance for this algorithm.
	double tempDistance = 0.0;
	int closestIndex = -1;
	int i, j;

	for(int i=0; i<TOTALFLORIST; ++i){
		for(j=0; j<TOTALFLOWERS; ++j){
			if(florists[i].flowers[j] == orderedFlower){
				tempDistance = euclideanDist(location, florists[i].location);
				if(tempDistance < closestF){
					closestF = tempDistance;
					closestIndex = i;
				}
			}
		}
	}


	return closestIndex;
}

int flowerToEnum(const char* flower){
	if(strcmp(flower, "orchid") == 0)
		return orchid;
	else if(strcmp(flower, "clove") == 0)
		return clove;
	else if(strcmp(flower, "daffodil") == 0)
		return daffodil;
	else if(strcmp(flower, "violet") == 0)
		return violet;
	else if(strcmp(flower, "rose") == 0)
		return rose;
	else
		return -1;
}

void prepareAndDeliverFlower(int time){
	sleep(time);
}

void* floristThread(void* floristNo){
	int oldIndex = -1;
	int queueIndex = 0;
	int preparationTime = 0;
	int deliveryTime = 0;
	int localFloristNo = (int) floristNo;
	flowerOrder newOrder;

	for(;;){

		pthread_mutex_lock(&mutex[localFloristNo]);

		while( isLastOrder == 0 && queueIndex >=orderSizes[localFloristNo]){
			 pthread_cond_wait(&cond[localFloristNo], &mutex[localFloristNo]);
		}
		newOrder = floristOrders[localFloristNo][queueIndex];
		pthread_mutex_unlock(&mutex[localFloristNo]);

		srand(time(NULL));
		preparationTime = rand()%41 + 10;
		deliveryTime = ((double) euclideanDist( florists->location , florists[localFloristNo].location) )* florists[localFloristNo].speed;
		prepareAndDeliverFlower( (deliveryTime + preparationTime)/1000000 );

		floristReturns[localFloristNo].totalTime  += deliveryTime + preparationTime;
		++floristReturns[localFloristNo].numSales;
		++queueIndex;
		fprintf(stderr, "Florist %s has delivered a ", florists[localFloristNo].name);
		fprintf(stderr, "%s", newOrder.flowerName);
		fprintf(stderr, " in %dms\n", (deliveryTime + preparationTime));


		if(isLastOrder == 1 && queueIndex >= orderSizes[localFloristNo]){
			fprintf(stderr, "%s is closing the shop\n", florists[localFloristNo].name);
			pthread_mutex_unlock(&mutex[localFloristNo]);
			break;
		}
	}	

	pthread_exit(NULL);

}