#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourPlusUndo.h"
#include "Cell.h"
#include <iostream>
#include <string>
#include <stdlib.h> //Exit
#include <fstream> //Read/Write files

using namespace std;

int myNameSpace::ConnectFourPlusUndo::undoLastMove(){
	int h = 0, w = 0;
	
	if(playsVector.size() != 0){
		h = playsVector[playsVector.size()-1].first; //Getting the Height of the last move
		w = playsVector[playsVector.size()-1].second; //Getting the Width of the last move
		gameBoard[h][w].setStatus("Empty");
		playsVector.pop_back();
		--livingCells;
		if(whosTurn == 1)
			whosTurn = 2;
		else
			whosTurn = 1;
		
		return 1;
	}
	else
		return 0;
}
