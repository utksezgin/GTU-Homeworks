#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include "ServerClient.h"

int callSocket(char *hostname, unsigned short portnum);

int main(int argc,char *argv[]){
	int sd, read_byte;
	char writeBuffer[BUFFER_SIZE];
	if(argc<6){
		fprintf(stderr, "Usage: ./clientApp name priority degree server address server port address");
		exit(1);
	}
	if( (sd = callSocket( argv[4], atoi(argv[5])) ) == -1){
		perror("Client");
		exit(-1);
	}
	sprintf(writeBuffer, "%s %c %d", argv[1], argv[2][0], atoi(argv[3]));
	fprintf(stderr, "Client %s requesting %c %d from server %s:%d\n",argv[1], argv[2][0], atoi(argv[3]),argv[4], atoi(argv[5]) );
	if(write(sd, writeBuffer, strlen(writeBuffer))<1){
		perror("");
		close(sd);
		exit(1);
	}
	r_read(sd, writeBuffer, sizeof(writeBuffer));

	fprintf(stderr, "%s\n", writeBuffer);

	close(sd);
	return 0;

}

//From previous year's slide (Network Communication (Basics)
int callSocket(char *hostname, unsigned short portnum){
	struct sockaddr_in sa;
	struct hostent *hp;
	int s;
	if ((hp= gethostbyname(hostname)) == NULL) { /* do we know the host's */
		errno= ECONNREFUSED; /* address? */
		return(-1); /* no */
	} /* if gethostname */
	memset(&sa,0,sizeof(sa));
	memcpy((char *)&sa.sin_addr,hp->h_addr,hp->h_length); /* set address */
	sa.sin_family= hp->h_addrtype;
	sa.sin_port= htons((u_short)portnum);
	if ((s= socket(hp->h_addrtype,SOCK_STREAM,0)) < 0) /* get socket */
		return(-1);
	if (connect(s,(struct sockaddr *)&sa,sizeof sa) < 0) { /* connect */
		close(s);
		return(-1);
	} /* if connect */
	return(s);
} 