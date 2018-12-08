#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"
#include "Cell.h"
#include <iostream>
#include <string>

using namespace std;

namespace myNameSpace{

class ConnectFourDiag : public ConnectFourAbstract{

	public:
		//Constructors
		ConnectFourDiag() : ConnectFourAbstract(){}; //Creates a 5x5 board game
		ConnectFourDiag(int w) : ConnectFourAbstract(w){}; //Creates a 5xWidth board game **Width cannot be less than 4 and greater than 26
		ConnectFourDiag(int h, int w) : ConnectFourAbstract(h, w){}; //Creates a HeightxWidth board game **Height and width cannot be less than 4 Width cannot be greater than 26
		ConnectFourDiag(const ConnectFourDiag& cF) : ConnectFourAbstract(cF){};//Copy Constructor
		ConnectFourDiag(string fileName)  : ConnectFourAbstract(fileName){};//Constructor that reads from the given filename
		
		
		int checkWinner() override; //Checks for winner horizontally or vertically /draw 1:Winner 2:Draw

};

}
#endif
