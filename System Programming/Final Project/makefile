all:
	gcc  -c server.c client.c
	gcc  server.o -o serverApp -pthread -lm
	gcc  client.o -o clientApp -pthread -lm
clean:
	rm -rf *o
