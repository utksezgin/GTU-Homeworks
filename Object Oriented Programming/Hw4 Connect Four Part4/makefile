all: hw01

hw01: main.o
	g++ -std=c++11 main.o Cell.o ConnectFour.o  -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp ConnectFour.cpp ConnectFour.h Cell.cpp Cell.h

clean:
	rm *.o exe *.gch

