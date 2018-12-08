all: hw

hw: main.o
	g++ -std=c++11 main.o -o exe -pedantic-errors

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o exe *.gch

