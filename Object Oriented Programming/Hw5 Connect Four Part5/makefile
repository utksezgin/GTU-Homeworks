all: hw01

hw01: main.o
	g++ -std=c++11 main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourPlusUndo.o ConnectFourDiag.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp ConnectFourDiag.h ConnectFourDiag.cpp ConnectFourPlusUndo.h ConnectFourPlusUndo.cpp ConnectFourPlus.cpp  ConnectFourPlus.h ConnectFourAbstract.cpp ConnectFourAbstract.h Cell.cpp Cell.h

clean:
	rm *.o exe *.gch

