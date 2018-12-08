all: hw01

hw01: main.o
	g++ -std=c++11 main.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o exe

