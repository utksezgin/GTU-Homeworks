#include "ConnectFourAbstract.h"
#include "Cell.h"
#include <iostream>
#include <string>
#include <stdlib.h> //Exit
#include <fstream> //Read/Write files
#include <math.h>
#include <vector>
using namespace std;


myNameSpace::ConnectFourAbstract::ConnectFourAbstract(){
	++objectCount;
	objectNumber = objectCount;
	whosTurn = 1;
	isAI = 0;
	maxHeight = 5;
	maxWidth = 5;
	playsVector.resize(0);
	
	//Allocating new memory for gameBoard with new sizes
	gameBoard = new Cell*[maxHeight];
	for(int i=0; i< maxHeight; ++i)
		gameBoard[i] = new Cell[maxWidth];
	
	//Initializing cells	
	for(int i=0; i<maxHeight; ++i){
		for(int j=0; j<maxWidth; ++j){
			gameBoard[i][j].setHeight(i);
			gameBoard[i][j].setWidth(j);
			gameBoard[i][j].setStatus("Empty");
		}
	}
		
}



myNameSpace::ConnectFourAbstract::ConnectFourAbstract(int w){
	const int MIN_WIDTH = 4; //Minimum board width
	const int MAX_WIDTH = 26; //Maximum board width
	++objectCount;
	objectNumber = objectCount;
	whosTurn = 1;
	isAI = 0;
	maxHeight = 5;
	playsVector.resize(0);
	
	if(w < MIN_WIDTH || w> MAX_WIDTH){
		cerr << "Width Cannot be less than 4 or greater than 26" << endl;
		exit(-1);
	}
	else{
		maxWidth = w;
		
		
	//Allocating new memory for gameBoard with new sizes
	gameBoard = new Cell*[maxHeight];
	for(int i=0; i< maxHeight; ++i)
	gameBoard[i] = new Cell[maxWidth];
		
		//Initializing cells	
		for(int i=0; i<maxHeight; ++i){
			for(int j=0; j<maxWidth; ++j){
				gameBoard[i][j].setHeight(i);
				gameBoard[i][j].setWidth(j);
				gameBoard[i][j].setStatus("Empty");
			}
		}	
	}
}




myNameSpace::ConnectFourAbstract::ConnectFourAbstract(int h, int w){
	const int MIN_HEIGHT = 4; //Minimum board height
	const int MIN_WIDTH = 4; //Minimum board width
	const int MAX_HEIGHT = 50; //Maximum board height
	const int MAX_WIDTH = 26; //Maximum board width
	playsVector.resize(0);
	
	++objectCount;
	objectNumber = objectCount;
	whosTurn = 1;
	isAI = 0;
	if(w < MIN_WIDTH || w > MAX_WIDTH || h < MIN_HEIGHT || h > MAX_HEIGHT){
		cerr << "Width Cannot be less than 4 or greater than 26, heigt cannot be less than 4" << endl;
		exit(-1);
	}
	else{
		maxHeight = h;
		maxWidth = w;
		
	//Allocating new memory for gameBoard with new sizes
	gameBoard = new Cell*[maxHeight];
	for(int i=0; i< maxHeight; ++i)
	gameBoard[i] = new Cell[maxWidth];
		
		//Initializing cells	
		for(int i=0; i<maxHeight; ++i){
			for(int j=0; j<maxWidth; ++j){
				gameBoard[i][j].setHeight(i);
				gameBoard[i][j].setWidth(j);
				gameBoard[i][j].setStatus("Empty");
			}
		}
	}
}


myNameSpace::ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& cF){
	this->isGameOver = cF.isGameOver;
	this->objectNumber = cF.objectNumber;
	this->whosTurn = cF.whosTurn;
	this->isAI = cF.isAI;
	this->maxWidth = cF.maxWidth;
	this->maxHeight = cF.maxHeight;
	this->playsVector = cF.playsVector;
	
	this->gameBoard = new Cell*[this->maxHeight];
	for(int i=0; i<this->maxHeight; ++i)
		this->gameBoard[i] = new Cell[this->maxWidth];
	
	
	for(int i=0; i<this->maxHeight; ++i){
		for(int j=0; j<this->maxWidth; ++j){
			this->gameBoard[i][j] = cF.gameBoard[i][j];
		}
	}	
}


myNameSpace::ConnectFourAbstract::ConnectFourAbstract(string fileName){
	loadFromFile(fileName);
	playsVector.resize(0);
}

int myNameSpace::ConnectFourAbstract::livingCells = 0;
int myNameSpace::ConnectFourAbstract::objectCount =0;


//Assignment opertor
myNameSpace::ConnectFourAbstract& myNameSpace::ConnectFourAbstract::operator=(const myNameSpace::ConnectFourAbstract& cF){
	//Self assignment check
	if(this->maxHeight != cF.maxHeight && this->maxWidth != cF.maxWidth){
		for(int i=0; i<maxHeight; ++i)
			delete [] gameBoard[i];
		delete [] gameBoard; 
		
		gameBoard = new Cell*[cF.maxHeight];
		for(int i=0; i<cF.maxHeight; ++i)
			gameBoard[i] = new Cell[cF.maxWidth];
	}
	
	this->maxHeight = cF.maxHeight;
	this->maxWidth = cF.maxWidth;
	
	for(int i=0; i<this->maxHeight; ++i){
		for(int j=0; j < this->maxWidth; ++j){
			this->gameBoard[i][j] = cF.gameBoard[i][j];
		}
	}	
	
}


//Getters
int myNameSpace::ConnectFourAbstract::getCellWidth(int height, int width) const {
	if(width > maxWidth || height > maxHeight){
		cerr << "Width Cannot be less than 4 or greater than 26, heigt cannot be less than 4" << endl;
		exit(-1);
	}
	else
		return gameBoard[height][width].getWidth();
}




int myNameSpace::ConnectFourAbstract::getCellHeight(int height, int width) const{
	if(width >= maxWidth || height >= maxHeight){
		cerr << "Width Cannot be less than 4 or greater than 26, heigt cannot be less than 4" << endl;
		exit(-1);
	}
	else
		return gameBoard[height][width].getHeight();
}
 
 
 
 
string myNameSpace::ConnectFourAbstract::getCellStatus(int height, int width) const {
	if(width > maxWidth || height > maxHeight){	
		cerr << "Width Cannot be less than 4 or greater than 26, heigt cannot be less than 4" << endl;
		exit(-1);
	}
	else
		return gameBoard[height][width].getStatus();
}



void myNameSpace::ConnectFourAbstract::makeMove(string player, int w){
	int row = 0;
	for(int i=maxHeight-1; i>-1; --i){
		if(gameBoard[i][w].getStatus() == "Empty"){
			row = i;
			i = -1;
		}
	}
	checkIllegalMove(w);
	gameBoard[row][w].setStatus(player);
	++livingCells;
	playsVector.push_back( make_pair(row, w) ); //Saving the move in playsVector.
}


void myNameSpace::ConnectFourAbstract::playGame(){
	const int MIN_HEIGHT = 4; //Minimum board height
	const int MIN_WIDTH = 4; //Minimum board width
	const int MAX_HEIGHT = 50; //Maximum board height
	const int MAX_WIDTH = 26; //Maximum board width
	const int firstFive = 5; //In order to skip 5 from input ("LOAD " and "SAVE ")
	string input;
	int isProper = 0;
	const int notAI = 0; //Parameter that player's move sends to checkIllegalMove as an argumant
	int newHeight = 0, newWidth = 0;
	
	
	//Taking Board sizes from the player.
	while(isProper == 0){
		cout << "Please enter Height from 4 to 50" << endl;
		cin >> input;
		newHeight = stringToInt(input);	
		if(newHeight < MIN_HEIGHT || newHeight > MAX_HEIGHT){
			cerr << "Wrong input" << endl;
			isProper=0;
			cin.clear();
		}
		else{
			isProper = 1;
			cin.clear();
		}
		if(isProper == 1){ //If Height input is legal
			cout << "Please enter Width from 4 to 26" << endl;
			cin >> input;
			newWidth = stringToInt(input);	
			if(newWidth < MIN_WIDTH || newWidth > MAX_WIDTH){
				cerr << "Wrong input" << endl;
				isProper=0;
				cin.clear();
			}
			else{
				isProper = 1;
				cin.clear();
			}
		}
	}
	
	resizeBoard(newHeight, newWidth);
	maxHeight = newHeight;
	maxWidth = newWidth;
	
	isProper = 0;
	char userChoice;
	while(isProper == 0){
		cout << "Please enter 'C' for playing against the computer or 'P' for playing against a player" << endl;
		cin.ignore();
		cin >> userChoice;
		if(userChoice == 'c' || userChoice == 'C'){
			isAI = 1;
			isProper = 1;
		}
		else if(userChoice == 'P' || userChoice == 'p'){
			isProper =1 ;
			isAI = 0;
		}
	}
	cin.ignore();
	printBoard();

	int lastMove =0; // If last move is made by 1st player it's 1 if 2nd player it's 2
	string command; //Holds the player's input
	int moveColumn; //Holds the choice of player's move
	int isGameOver = -1;
	int commandNo = -1; //0 for save, 1 for load, 2 for move -1 for unknown inputs
	string fileName; //Holds the name of the file name that user has given.	
	
	
	while(isGameOver == -1){
		
		isProper = -1;
		while( isProper == -1 && whosTurn == 1){
			cout << "Player 1's Turn, Make your move." << endl << endl;
			cin.clear();
			getline(std::cin, command);
			if(command.length() == 0 || cin.eof() ){ //EoF Check
				cerr << "End of file" << endl;
				exit(0);
			}
			commandNo = checkCommand(moveColumn, command);
			switch (commandNo) {
				case 0:
					//Getting fileName from Load Command
					if( command.length() > firstFive){
					for(int k=firstFive, i=0; k<command.length(); ++k, ++i)
						fileName[i] = command[k];
						saveToFile(fileName);
					}
					else
						cerr << "Unknown input. Couldn't find the file name" << endl;
					break;
				case 1:
					//Getting fileName from Load Command
					if( command.length() > firstFive){
						for(int k=firstFive,  i=0; k<command.length(); ++k, ++i)
							fileName[i] = command[k];
						loadFromFile(fileName);
					}
					else
						cerr << "Unknown input. Couldn't find the file name" << endl;
					break;
				case 2:
					if( command.length() == 1){
						isProper = 1;
						moveColumn = charToInt(command[0]);
						play(moveColumn);
						whosTurn = 2;
						printBoard();
						lastMove = 1;
						isGameOver = checkWinner();
					}
					else
						cerr << "Illegal Move" << endl;	
					break;
				case 3:
					int undo;
					undo = undoLastMove();
					if( undo == 1 ) {
						cout << "Successful undo" << endl;
						printBoard();
					}
					else if(undo == 0)
						cerr << "Cannot undo on empty board" << endl;
					break;
				case -1:
					cerr << "Unknown Command" << endl;
					break;				
			}	
			command.clear();		
		}
		
		if(isGameOver == -1 && whosTurn == 2){
			if(isAI == 1){
				cout << "Comptuer's Turn." << endl << endl;
				play();
				printBoard();
				whosTurn = 1;
				lastMove = 2;
			}			
			else{
				isProper = -1;
				while( isProper == -1){
					cout << "Player 2's Turn, Make your move." << endl << endl;
					cin.clear();
					getline(std::cin, command);
					if(command.length() == 0){ //EoF Check
						cerr << "End of file" << endl;
						exit(0);
					}
					commandNo = checkCommand(moveColumn, command);
					switch (commandNo) {
						case 0:
							//Getting fileName from Load Command
							if( command.length() > firstFive){
							for(int k=firstFive, i=0; k<command.length(); ++k, ++i)
								fileName[i] = command[k];
							saveToFile(fileName);
							}
							else
								cerr << "Unknown input. Couldn't find the file name" << endl;
							break;
						case 1:
							//Getting fileName from Load Command
							if( command.length() > firstFive){
								for(int k=firstFive,  i=0; k<command.length(); ++k, ++i)
									fileName[i] = command[k];
								loadFromFile(fileName);
							}
							else
								cerr << "Unknown input. Couldn't find the file name" << endl;
							break;
						case 2:
							if( command.length() == 1){
								isProper = 1;
								moveColumn = charToInt(command[0]);
								play(moveColumn);
								whosTurn = 1;
								printBoard();
								isGameOver = checkWinner();
							}
							else
								cerr << "Illegal Move" << endl;	
							break;
						case 3:
							if( undoLastMove() ) {
								cout << "Successful undo" << endl;
								printBoard();
							}
							else
								cerr << "Failed to undo the play" << endl;
							break;
						case -1:
							cerr << "Unknown Command" << endl;
							break;				
					}	
					command.clear();
				}
			}
			lastMove = 2;
			cout << "Current Living cell number: " << livingCells << endl;
			isGameOver = checkWinner();
		}
		if( cin.eof() ){
			exit(0);
		}
	}
	
	if(isGameOver == 1){
		if(isAI == 1 && lastMove == 2)
			cout << "Computer won!!!" << endl;
		else
			cout << "Player " << lastMove << " won!!!" << endl << endl;
	}
	else if( isGameOver == 2 )
		cout << "DRAW!!" << endl << endl;
	
	printBoard(); //Printing the final board
	
	
}


int myNameSpace::ConnectFourAbstract::charToInt(char c){
	int num=0;
	if( c>='a' && c<='z' )
		num = c-97;
	else if ( c>='A' && c<='Z' )
		num = c-65;
		
	return num;
}

void myNameSpace::ConnectFourAbstract::resizeBoard(int newHeight, int newWidth){
	
	//Freeing gameBoard
	for(int i=0; i<maxHeight; ++i)
		delete [] gameBoard[i];
	delete [] gameBoard;
	
	//Allocating new memory for gameBoard with new sizes
	gameBoard = new Cell*[newHeight];
	for(int i=0; i< newHeight; ++i)
		gameBoard[i] = new Cell[newWidth];	

	//Changing old height and width with new ones
	maxHeight = newHeight;
	maxWidth = newWidth;
}




int myNameSpace::ConnectFourAbstract::checkCommand(int column, string input){
	if( (input[0]=='S' && input[1]=='A' && input[2]=='V' && input[3]=='E') || (input[0]=='s' && input[1]=='a' && input[2]=='v' && input[3]=='e') )
		return 0;
	else if( (input[0]=='L' && input[1]=='O' && input[2]=='A' && input[3]=='D') || (input[0]=='l' && input[1]=='o' && input[2]=='a' && input[3]=='d') )
		return 1;
	else if( (input[0]=='U' && input[1]=='N' && input[2]=='D' && input[3]=='O') || (input[0]=='u' && input[1]=='n' && input[2]=='d' && input[3]=='o') )
		return 3;
	else if( checkIllegalMove(charToInt(input[0])) == 1)
		return 2;
	else
		return -1;
}


int myNameSpace::ConnectFourAbstract::checkIllegalMove(int w){
	int isIllegal =-1;
	if(maxWidth > w){
		for(int i=maxHeight-1; i>=0; --i){
			if(gameBoard[i][w].getStatus() == "Empty" && gameBoard[i][w].getIsPlayable() == 1){
				isIllegal = 1;
			}
		}
	}
	if(isIllegal == -1 && isAI == 0)
		cerr << "Illegal Move" << endl;
	return isIllegal;		
}



void myNameSpace::ConnectFourAbstract::readBoard(string fileName){
	fstream boardF;
	string line;
	int lineCount = 0;
	int lineWidth = 0;
	
	
	//Configuring board length and width
	boardF.open(fileName.c_str(), std::fstream::in);//Opening board file	
	if( boardF.is_open() ){
		while ( getline (boardF,line) ){
			++lineCount;
			if(line.length() > lineWidth)
				lineWidth = line.length();
		}
	}
	else{
		cerr << "Couldn't open the board file" << endl;
		exit(-1);
	}
	//Closing the file
	boardF.close();
	
	//Resizing board accordingly
	resizeBoard(lineCount, lineWidth);
	
	//Reopening the board to fill the board
	boardF.open(fileName.c_str(), std::fstream::in);//Opening board file	
	if( boardF.is_open() ){
		int i=0;
		while ( getline (boardF,line) ){
			for(int k=0; k< line.length(); ++k){
				if(line[k] ==' '){
					gameBoard[i][k].setStatus("Empty");
					gameBoard[i][k].setIsPlayable(0);
				}
				else if(line[k] =='*'){
					gameBoard[i][k].setStatus("Empty");
					gameBoard[i][k].setIsPlayable(1);
				}
				else if(line[k] =='X'){
					gameBoard[i][k].setStatus("User1");
					gameBoard[i][k].setIsPlayable(1);
				}
				else if(line[k] =='O'){
					if(isAI == 0)
						gameBoard[i][k].setStatus("User2");
					else if(isAI == 1)
						gameBoard[i][k].setStatus("Computer");
					gameBoard[i][k].setIsPlayable(1);
				}
			}
			++i;
		}
	}
	else{
		cerr << "Couldn't open the board file" << endl;
		exit(-1);
	}
	//Closing the file
	boardF.close();
	
}

void myNameSpace::ConnectFourAbstract::loadFromFile(string loadFile){
	fstream loadF;
	int newHeight, newWidth;
	string line; //The line that we read from save file
	string temp; //Temp string for parsing
	string temp2;
	temp2.resize(0);
	loadF.open(loadFile.c_str(), std::fstream::in);//Opening text file
	
	if( loadF.is_open() ){
		while ( getline (loadF,line) );//Reading the line from savefile
		
		int i=0;
		if(line.length() < 1){
			cerr << "Corrupted save file" << endl;
			exit(-1);	
		}
		else{
			while(line[i] != ' '){ //Reading Height from line string
				temp += line[i];
				++i;
			}
			newHeight = stringToInt(temp);
			++i; //Skipping empty cell
			temp.clear(); //Clearing temp string
			temp.resize(0);//
						
			while(line[i] != ' '){ //Reading Width from line string
				temp += line[i];
				++i;
			}
			
			newWidth = stringToInt(temp);
			++i; //Skipping empty cell
			temp.clear(); //Clearing temp string
			temp.resize(0);//
			
			while(line[i] != ' '){ //Reading isAI from line string
				temp += line[i];
				++i;
			}
			isAI = stringToInt(temp);
			++i; //Skipping empty cell 
			temp.clear(); //Clearing temp string
			temp.resize(0);
			
			while(line[i] != ' '){ //Reading whosTurn from line string
				temp += line[i];
				++i;
			}
			whosTurn = stringToInt(temp);
			++i; //Skipping empty cell 
			temp.clear(); //Clearing temp string
			
			while(line[i]!= ' '){
				while(line[i]!=','){
					temp += line[i];
					++i;
				}
				++i;
				while(line[i]!=','){
					temp2 += line[i];
					++i;
				}	
				playsVector.push_back(make_pair( stringToInt(temp), stringToInt(temp2) ) );
				++i;
				temp.clear();
				temp2.clear();
			}
			++i; //Skipping empty cell
			temp.clear(); //Clearing temp string
			temp.resize(0);
			
			resizeBoard(newHeight, newWidth);
			
			int j=0, k=0;
			while(i<line.length() && j<maxHeight && k<maxWidth){
				gameBoard[j][k].setHeight(j);
				gameBoard[j][k].setHeight(k);
				if(line[i] == '.')
					gameBoard[j][k].setStatus("Empty");
				else if(line[i] == ' '){
					gameBoard[j][k].setStatus("Empty");
					gameBoard[j][k].setIsPlayable(0);
				}
				else if(line[i] == '1')
					gameBoard[j][k].setStatus("User1");
				else if(line[i] == '2')
					gameBoard[j][k].setStatus("User2");
				else if(line[i] == 'c')
					gameBoard[j][k].setStatus("Computer");
				++k;
				if(k == maxWidth){
					k=0;
					++j;
				}
				++i;
			}
			cout << "Game successfully loaded" << endl;
			printBoard();		
		}
	}
	else{
		cerr << "Couldn't open the file" << endl;
		exit(-1);
	}
	loadF.close();
}




void myNameSpace::ConnectFourAbstract::saveToFile(string saveFile){
	ofstream saveF;
	
	saveF.open(saveFile.c_str());//Opening text file
	
	if( saveF.is_open() ){ //Checking if file is open successfully
		saveF << maxHeight << " " << maxWidth << " " << isAI << " " << whosTurn << " "; //Saving boardSize, isAI, isGameOver
		
	//Saving moves	
	for(int i=0; i<playsVector.size(); ++i ){
		saveF << playsVector[i].first;
		saveF << ",";
		saveF << playsVector[i].second;
		saveF << ",";
	}
		saveF << " ";
	cout << "?" << endl;
		for(int i=0; i<maxHeight; ++i){ //Saving board
			for(int j=0; j<maxWidth; ++j){
				if(gameBoard[i][j].getStatus()=="Empty"){
					if(gameBoard[i][j].getIsPlayable() == 1)
						saveF << '.';
					else
						saveF << ' ';
				}
				else if(gameBoard[i][j].getStatus()=="User1")
					saveF << '1';
				else if(gameBoard[i][j].getStatus()=="User2")
					saveF << '2';
				else if(gameBoard[i][j].getStatus()=="Computer")
					saveF<< 'c';	
			}			
		}
		cout << "Game is successfully saved!" << endl; 
	}
	else
		cerr << "Couldn't open the file" << endl;
	
	saveF.close(); //Closing the file
}





int myNameSpace::ConnectFourAbstract::stringToInt(string str){
	int number=0;
	for(int i=0; i<str.length(); ++i){
		number+= ( (str[i]-'0') * pow(10, (str.length()-i-1) ));
	}
	return number;
}





void myNameSpace::ConnectFourAbstract::printBoard(){
	char column = 'A';
	for(int i=0; i<maxWidth; ++i){
		cout << column;
		++column;
	}
	
	cout << endl;
		
	
	
	for(int i=0; i<maxHeight; ++i){
		for(int j=0; j<maxWidth; ++j){
			if(gameBoard[i][j].getIsPlayable() == 1){
				if(gameBoard[i][j].getStatus() == "Empty")
					cout << '.';
				else if(gameBoard[i][j].getStatus() == "User1")
						if( gameBoard[i][j].getWinnerCell() )
							cout << 'x';
						else
							cout << 'X';
				else
					if( gameBoard[i][j].getWinnerCell() )
						cout << 'o';
					else
						cout << 'O';
				}
			else
				cout << ' ';
			}
			cout << endl;
		
	}
	cout << endl;
}



void myNameSpace::ConnectFourAbstract::play(int move){
	string player;
	if(whosTurn == 1)
		player = "User1";
	else
		player = "User2";
	if( checkIllegalMove(move) ){
		makeMove(player, move);
	}
	else
		cerr << "Illegal Move" << endl;
}




void myNameSpace::ConnectFourAbstract::play(){
	int isMadeMove = 0; //0 If bot haven't made a move yet.
	const int OFFSET = 3; //Offset for checking board Vertical/Horizontal
	const int isAI = 1;   // Parameter for checkIllegalMove function to ignore illegal move err for AI.

	int moveI = -1;		//Coordinates of move
	int moveJ = -1;		//If these stay as -1 there's no lose threat in the game
	//AI Checks if there's a winning move
		for(int i=0; i<maxHeight; ++i){   //i stands for rows
			for(int j=0; j<maxWidth; ++j){ //j stands for columns
				if(gameBoard[i][j].getStatus() == "Computer"){ //Checks if there's his token	
					if(j<maxWidth-OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i][j+1].getStatus()){       	//Checking rightwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i][j+2].getStatus()){		//horizontal
								if(gameBoard[i][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+1][j+3].getStatus() != "Empty"){
											moveI = i;
											moveJ = j+3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i][j-1].getStatus()){       	//Checking leftwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i][j-2].getStatus()){		//horizontal
								if(gameBoard[i][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+1][j-3].getStatus() != "Empty"){
											moveI = i;
											moveJ = j-3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i;
										moveJ = j-3;
									}
								}
							}
						}
					}
					if(i<maxHeight-OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j].getStatus()){       	//Checking downwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j].getStatus()){		//vertical
								if(gameBoard[i+3][j].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+3+1][j].getStatus() != "Empty"){
											moveI = i+3;
											moveJ = j;
										}
									}
									else if( i == maxHeight -1){
										moveI = i+3;
										moveJ = j;
									}
								}
							}
						}
					}
					if(i>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j].getStatus()){       	//Checking upwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j].getStatus()){		//vertical
								if(gameBoard[i-3][j].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i-3+1][j].getStatus() != "Empty"){
											moveI = i-3;
											moveJ = j;
										}
									}
									else if( i == maxHeight -1){
										moveI = i-3;
										moveJ = j;
									}
								}
							}
						}
					}
					if(i>OFFSET-1 && j<maxWidth - OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j+1].getStatus()){       	//Top-Right      
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j+2].getStatus()){		//Diagonal
								if(gameBoard[i-3][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[-3+1][j+3].getStatus() != "Empty"){
											moveI = i-3;
											moveJ = j+3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i-3;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j-1].getStatus()){       	//Top-Left     
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j-2].getStatus()){		//Diagonal
								if(gameBoard[i-3][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i-3+1][j-3].getStatus() != "Empty"){
											moveI = i-3;
											moveJ = j-3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i-3;
										moveJ = j-3;
									}
								}
							}
						}
					}
					if(i<maxHeight - OFFSET && j<maxWidth - OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j+1].getStatus()){       	//Bottom-Right      
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j+2].getStatus()){		//Diagonal
								if(gameBoard[i+3][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+3+1][j+3].getStatus() != "Empty"){
											moveI = i+3;
											moveJ = j+3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i+3;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(i<maxHeight - OFFSET && j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j-1].getStatus()){       	//Bottom-Left     
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j-2].getStatus()){		//Diagonal
								if(gameBoard[i+3][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+3+1][j-3].getStatus() != "Empty"){
											moveI = i+3;
											moveJ = j-3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i+3;
										moveJ = j-3;
									}
								}
							}
						}
					}
				}
			}
		}	
	if(moveI != -1 && moveJ != -1){ //If there's a losing threat
		makeMove("Computer", moveJ);
		isMadeMove = 1;
	}
	else if( isMadeMove == 0){ //If there's no losing threat, AI makes it's own move 
	

	//Checks if the enemy has a winning move
		for(int i=0; i<maxHeight; ++i){   //i stands for rows
			for(int j=0; j<maxWidth; ++j){ //j stands for columns
				if(gameBoard[i][j].getStatus() == "User1"){ //Checks if it's enemy token		
					if(j<maxWidth-OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i][j+1].getStatus()){       	//Checking rightwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i][j+2].getStatus()){		//horizontal
								if(gameBoard[i][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+1][j+3].getStatus() != "Empty"){
											moveI = i;
											moveJ = j+3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i][j-1].getStatus()){       	//Checking leftwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i][j-2].getStatus()){		//horizontal
								if(gameBoard[i][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+1][j-3].getStatus() != "Empty"){
											moveI = i;
											moveJ = j-3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i;
										moveJ = j-3;
									}
								}
							}
						}
					}
					if(i<maxHeight-OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j].getStatus()){       	//Checking downwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j].getStatus()){		//vertical
								if(gameBoard[i+3][j].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+3+1][j].getStatus() != "Empty"){
											moveI = i+3;
											moveJ = j;
										}
									}
									else if( i == maxHeight -1){
										moveI = i+3;
										moveJ = j;
									}
								}
							}
						}
					}
					if(i>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j].getStatus()){       	//Checking upwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j].getStatus()){		//vertical
								if(gameBoard[i-3][j].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i-3+1][j].getStatus() != "Empty"){
											moveI = i-3;
											moveJ = j;
										}
									}
									else if( i == maxHeight -1){
										moveI = i-3;
										moveJ = j;
									}
								}
							}
						}
					}
					if(i>OFFSET-1 && j<maxWidth - OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j+1].getStatus()){       	//Top-Right      
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j+2].getStatus()){		//Diagonal
								if(gameBoard[i-3][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i-3+1][j+3].getStatus() != "Empty"){
											moveI = i-3;
											moveJ = j+3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i-3;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j-1].getStatus()){       	//Top-Left     
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j-2].getStatus()){		//Diagonal
								if(gameBoard[i-3][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i-3][j-3].getStatus() != "Empty"){
											moveI = i-3;
											moveJ = j-3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i-3;
										moveJ = j-3;
									}
								}
							}
						}
					}
					if(i<maxHeight - OFFSET && j<maxWidth - OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j+1].getStatus()){       	//Bottom-Right      
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j+2].getStatus()){		//Diagonal
								if(gameBoard[i+3][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+3+1][j+3].getStatus() != "Empty"){
											moveI = i+3;
											moveJ = j+3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i+3;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(i<maxHeight - OFFSET && j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j-1].getStatus()){       	//Bottom-Left     
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j-2].getStatus()){		//Diagonal
								if(gameBoard[i+2][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameBoard[i+3+1][j-3].getStatus() != "Empty"){
											moveI = i+3;
											moveJ = j-3;
										}
									}
									else if( i == maxHeight -1){
										moveI = i+3;
										moveJ = j-3;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	if(moveI != -1 && moveJ != -1 && isMadeMove == 0){
		if( checkIllegalMove(moveJ) ){
			makeMove("Computer", moveJ);
		}
	}
	else if( isMadeMove == 0){ //There's no winning or blocking move so Computer makes a random move.
		int randomColumn;
		int isIllegal;
		do{
			srand (time(NULL));
			randomColumn = rand() % maxWidth;
			isIllegal = checkIllegalMove(randomColumn);
		}
		while(isIllegal != 1);
			makeMove("Computer", randomColumn);
	}
}

myNameSpace::ConnectFourAbstract::~ConnectFourAbstract(){

	for(int i=0; i<maxHeight; ++i){
		for(int j=0; j<maxWidth; ++j){
			if(gameBoard[i][j].getStatus()!= "Empty")
				--livingCells;
		}
	}
		
	for(int i=0; i<maxHeight; ++i){
		delete []gameBoard[i];
	}
	delete []gameBoard;
}
