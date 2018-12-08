#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "Cell.h"
#include <iostream>
#include <string>

using namespace std;

namespace myNameSpace{

class ConnectFourPlusUndo : public ConnectFourPlus{

	public :
			//Constructors
			ConnectFourPlusUndo() : ConnectFourPlus(){}; //Creates a 5x5 board game
			ConnectFourPlusUndo(int w) : ConnectFourPlus(w){}; //Creates a 5xWidth board game **Width cannot be less than 4 and greater than 26
			ConnectFourPlusUndo(int h, int w) : ConnectFourPlus(h, w){}; //Creates a HeightxWidth board game **Height and width cannot be less than 4 Width cannot be greater than 26
			ConnectFourPlusUndo(const ConnectFourPlus& cF) : ConnectFourPlus(cF){};//Copy Constructor
			ConnectFourPlusUndo(string fileName)  : ConnectFourPlus(fileName){};//Constructor that reads from the given filename
		
		
		int undoLastMove() override;  //Returns 0 if the game is back to start, 1 for successful undo

};

}
#endif
