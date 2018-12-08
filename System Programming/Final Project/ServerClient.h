#define ITERATION_COUNT 6// Number of iterations in Taylor Series.
#define MAX_NAME_SIZE 256
#define BUFFER_SIZE 1024
#define MAX_QUEUE_SIZE 2
#define MAX_CONNECTION 30
#define TRUE 1
#define FALSE 0

//Provider Struct
typedef struct provider{
	char name[MAX_NAME_SIZE];
	int providerNo;
	int performance;
	int price;
	int duration;
	int isAvailable;
	int isFinished;
	int qIndex;
}provider;

//Client Struct
typedef struct client{
	char name[MAX_NAME_SIZE];
	char priority;
	int degree;
	int socketId;
	int clientNo;
}client;


//From the last year's book.
ssize_t r_read(int fd, void *buf, size_t size) {
    ssize_t retval;
    while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
    return retval;
}
