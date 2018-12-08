//Azmi Utku Sezgin 131044048 HW05

#include <iostream>
#include <string> //String Functions
#include <stdlib.h>//Included to create a random number with srand/rand
#include <time.h>  //Same as stdlib.h time()
#include <math.h> //Pow function
#include <fstream> //Read/Write files
#include "Cell.h"	//Cell Class
#include "ConnectFourAbstract.h" //ConnectFour Class
#include "ConnectFourPlus.h" //ConnectFour Class
#include "ConnectFourDiag.h" //ConnectFour Class
#include "ConnectFourPlusUndo.h" //ConnectFour Class
#include <fstream> //Read/Write files
using namespace std;

int main(){
	//ConnectFour file("save3.txt"); //Constructor works with filename
	char objectType;
	char properInput = 0;
	int maxHeight = 0; //Temporary variables to use on 
	int maxWidth = 0; //ConnectFour::resizeBoard function
	const int MIN_GAME = 2; //Minimum game amount a player can play at the same time except for singleplay.
	const int MAX_GAME = 10; //Maximum game amount a player can play at the same time.
	const int MIN_HEIGHT = 4; //Minimum board height
	const int MIN_WIDTH = 4; //Minimum board width
	const int MAX_HEIGHT = 50; //Maximum board height
	const int MAX_WIDTH = 26; //Maximum board width
	
	cout << "Welcome to Connect Four! Select your game mode." << endl;
	while(properInput == 0){
		cin >> objectType;
		if(objectType == 'P' || objectType == 'p'){ //Plus
			objectType = 'P';
			properInput = 1;
		}
		else if(objectType == 'D' || objectType == 'd'){ //Diagonal
			objectType = 'D';
			properInput = 1;
		}
		else if(objectType == 'U' || objectType == 'u'){ //Undo
			objectType = 'U';
			properInput = 1;
		}
		else{
			properInput =0;
			cerr << "Unknown input, Please enter 'P', 'D' or 'U' to start the game" << endl;
		}
	}
	if(objectType =='P'){
		myNameSpace::ConnectFourPlus plusGame;
		plusGame.playGame();
	}
	else if(objectType =='D'){
		myNameSpace::ConnectFourDiag diagGame;
		diagGame.playGame();
	}
	else if(objectType =='U'){
		myNameSpace::ConnectFourPlusUndo plusUndoGame;
		plusUndoGame.playGame();
	}
		
	cout << "Thanks for playing!" << endl;
		
	return 0;
}
