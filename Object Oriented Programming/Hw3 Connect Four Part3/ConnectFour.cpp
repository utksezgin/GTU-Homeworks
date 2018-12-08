#include "ConnectFour.h"
#include "Cell.h"
#include <iostream>
#include <string>
#include <stdlib.h> //Exit
#include <fstream> //Read/Write files
#include <math.h>
using namespace std;


ConnectFour::ConnectFour(){
	++objectCount;
	objectNumber = objectCount;
	whosTurn = 1;
	isAI = 0;
	maxHeight = 4;
	maxWidth = 4;
	resizeBoard(maxHeight, maxWidth);
	
	//Initializing cells	
	for(int i=0; i<maxHeight; ++i){
		for(int j=0; j<maxWidth; ++j){
			gameCells[i][j].setHeight(i);
			gameCells[i][j].setWidth(j);
			gameCells[i][j].setStatus("Empty");
		}
	}
		
}



ConnectFour::ConnectFour(int w){
	const int MIN_WIDTH = 4; //Minimum board width
	const int MAX_WIDTH = 26; //Maximum board width
	++objectCount;
	objectNumber = objectCount;
	whosTurn = 1;
	isAI = 0;
	maxHeight = 4;
	if(w < MIN_WIDTH || w> MAX_WIDTH){
		cerr << "Width Cannot be less than 4 or greater than 26" << endl;
		exit(-1);
	}
	else{
		maxWidth = w;
		resizeBoard(maxHeight, maxWidth);
		
		//Initializing cells	
		for(int i=0; i<maxHeight; ++i){
			for(int j=0; j<maxWidth; ++j){
				gameCells[i][j].setHeight(i);
				gameCells[i][j].setWidth(j);
				gameCells[i][j].setStatus("Empty");
			}
		}	
	}
}




ConnectFour::ConnectFour(int h, int w){
	const int MIN_HEIGHT = 4; //Minimum board height
	const int MIN_WIDTH = 4; //Minimum board width
	const int MAX_HEIGHT = 50; //Maximum board height
	const int MAX_WIDTH = 26; //Maximum board width
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
		resizeBoard(maxHeight, maxWidth);
		
		//Initializing cells	
		for(int i=0; i<maxHeight; ++i){
			for(int j=0; j<maxWidth; ++j){
				gameCells[i][j].setHeight(i);
				gameCells[i][j].setWidth(j);
				gameCells[i][j].setStatus("Empty");
			}
		}
	}
}

ConnectFour::ConnectFour(string fileName){
	loadFromFile(fileName);
}


int ConnectFour::livingCells = 0;
int ConnectFour::objectCount =0;

void ConnectFour::playGame(){
	const int MIN_HEIGHT = 4; //Minimum board height
	const int MIN_WIDTH = 4; //Minimum board width
	const int MAX_HEIGHT = 50; //Maximum board height
	const int MAX_WIDTH = 26; //Maximum board width
	const int firstFive = 5; //In order to skip 5 from input ("LOAD " and "SAVE ")
	string input;
	int isProper = 0;
	const int notAI = 0; //Parameter that player's move sends to checkIllegalMove as an argumant
	
	
	//Taking Board sizes from the player.
	while(isProper == 0){
		cout << "Please enter Height from 4 to 50" << endl;
		cin >> input;
		maxHeight = stringToInt(input);	
		if(maxHeight < MIN_HEIGHT || maxHeight > MAX_HEIGHT){
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
			maxWidth = stringToInt(input);	
			if(maxWidth < MIN_WIDTH || maxWidth > MAX_WIDTH){
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
	
	resizeBoard(maxHeight, maxWidth);
	
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


int ConnectFour::charToInt(char c){
	int num=0;
	if( c>='a' && c<='z' )
		num = c-97;
	else if ( c>='A' && c<='Z' )
		num = c-65;
		
	return num;
}

void ConnectFour::resizeBoard(int newHeight, int newWidth){
	gameCells.resize(newHeight);
	for(int i=0; i<newHeight; ++i){
		gameCells[i].resize(newWidth);
	}
	maxHeight = newHeight;
	maxWidth = newWidth;
}




int ConnectFour::checkCommand(int column, string input){
	if( (input[0]=='S' && input[1]=='A' && input[2]=='V' && input[3]=='E') || (input[0]=='s' && input[1]=='a' && input[2]=='v' && input[3]=='e') )
		return 0;
	else if( (input[0]=='L' && input[1]=='O' && input[2]=='A' && input[3]=='D') || (input[0]=='l' && input[1]=='o' && input[2]=='a' && input[3]=='d') )
		return 1;
	else if( checkIllegalMove(charToInt(input[0])) == 1)
		return 2;
	else
		return -1;
}


int ConnectFour::getCellWidth(int height, int width) const {
	if(width > maxWidth || height > maxHeight){
		cerr << "Width Cannot be less than 4 or greater than 26, heigt cannot be less than 4" << endl;
		exit(-1);
	}
	else
		return gameCells[height][width].getWidth();
}




int ConnectFour::getCellHeight(int height, int width) const{
	if(width >= maxWidth || height >= maxHeight){
		cerr << "Width Cannot be less than 4 or greater than 26, heigt cannot be less than 4" << endl;
		exit(-1);
	}
	else
		return gameCells[height][width].getHeight();
}
 
 
 
 
string ConnectFour::getCellStatus(int height, int width) const {
	if(width > maxWidth || height > maxHeight){	
		cerr << "Width Cannot be less than 4 or greater than 26, heigt cannot be less than 4" << endl;
		exit(-1);
	}
	else
		return gameCells[height][width].getStatus();
}


void ConnectFour::makeMove(string player, int w){
	int row = 0;
	for(int i=maxHeight-1; i>-1; --i){
		if(gameCells[i][w].getStatus() == "Empty"){
			row = i;
			i = -1;
		}
	}
	checkIllegalMove(w);
	gameCells[row][w].setStatus(player);
	++livingCells;
}



int ConnectFour::checkIllegalMove(int w){
	int isIllegal =-1;
	if(maxWidth > w){
		for(int i=maxHeight-1; i>=0; --i){
			if(gameCells[i][w].getStatus() == "Empty"){
				isIllegal = 1;}
		}
	}
	if(isIllegal == -1 && isAI == 0)
		cerr << "Illegal Move" << endl;
	return isIllegal;		
}



void ConnectFour::loadFromFile(string loadFile){
	fstream loadF;
	string line; //The line that we read from save file
	string temp; //Temp string for parsing
	
	loadF.open(loadFile.c_str(), std::fstream::in);//Opening text file
	
	if( loadF.is_open() ){
		while ( getline (loadF,line) );//Reading the line from savefile
		
		int i=0;
		if(line.length() < 1)
			cerr << "Corrupted save file" << endl;
		else{
			while(line[i] != ' '){ //Reading Height from line string
				temp += line[i];
				++i;
			}
			maxHeight = stringToInt(temp);
			++i; //Skipping empty cell
			temp.clear(); //Clearing temp string
			temp.resize(0);//
						
			while(line[i] != ' '){ //Reading Width from line string
				temp += line[i];
				++i;
			}
			
			maxWidth = stringToInt(temp);
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
			
			resizeBoard(maxHeight, maxWidth);
			
			int j=0, k=0;
			while(i<line.length() && j<maxHeight && k<maxWidth){
				gameCells[j][k].setHeight(j);
				gameCells[j][k].setHeight(k);
				if(line[i] == '.')
					gameCells[j][k].setStatus("Empty");
				else if(line[i] == '1')
					gameCells[j][k].setStatus("User1");
				else if(line[i] == '2')
					gameCells[j][k].setStatus("User2");
				else if(line[i] == 'c')
					gameCells[j][k].setStatus("Computer");
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
}




void ConnectFour::saveToFile(string saveFile){
	ofstream saveF;
	
	saveF.open(saveFile.c_str());//Opening text file
	
	if( saveF.is_open() ){ //Checking if file is open successfully
		saveF << maxHeight << " " << maxWidth << " " << isAI << " " << whosTurn << " "; //Saving boardSize, isAI, isGameOver
		
		for(int i=0; i<maxHeight; ++i){ //Saving board
			for(int j=0; j<maxWidth; ++j){	
				if(gameCells[i][j].getStatus()=="Empty")
					saveF << '.';
				else if(gameCells[i][j].getStatus()=="User1")
					saveF << '1';
				else if(gameCells[i][j].getStatus()=="User2")
					saveF << '2';
				else if(gameCells[i][j].getStatus()=="Computer")
					saveF<< 'c';
					
			}			
		}
		cout << "Game is successfully saved!" << endl; 
	}
	else
		cerr << "Couldn't open the file" << endl;
	
	saveF.close(); //Closing the file
}





int ConnectFour::stringToInt(string str){
	int number=0;
	for(int i=0; i<str.length(); ++i){
		number+= ( (str[i]-'0') * pow(10, (str.length()-i-1) ));
	}
	return number;
}





void ConnectFour::printBoard(){
	char column = 'A';	
	for(int i=0; i<maxWidth; ++i){
		cout << column;
		++column;
	}
	
	cout << endl;
		
	
	for(int i=0; i<maxHeight; ++i){
		for(int j=0; j<maxWidth; ++j){
			if(gameCells[i][j].getStatus() == "Empty")
				cout << '.';
			else if(gameCells[i][j].getStatus() == "User1")
					if( gameCells[i][j].getWinnerCell() )
						cout << 'x';
					else
						cout << 'X';
			else
				if( gameCells[i][j].getWinnerCell() )
					cout << 'o';
				else
					cout << 'O';
		}
		cout << endl;
	}
	cout << endl;
}



int ConnectFour::checkWinner(){
	const int OFFSET = 3;
	int isWinner = 2; //Set to 2 by default. 2 Stands for draw.
	int winnerCell =1;
	//Checking for Draw.
	for(int i=0; i<maxHeight; ++i){   //i stands for columns
		for(int j=0; j<maxWidth; ++j){ //j stands for rows
			if(gameCells[i][j].getStatus() == "Empty"){ //If there's an empty cell, it's not draw
				isWinner = -1;
			}
		}
	}
	
	for(int i=0; i<maxHeight; ++i){   //i stands for columns
		for(int j=0; j<maxWidth; ++j){ //j stands for rows
			if(gameCells[i][j].getStatus() != "Empty"){ //Checks if that cell is empty			
				if(j<maxWidth-OFFSET){ //Preventing overflow
					if(gameCells[i][j].getStatus() == gameCells[i][j+1].getStatus() ){       	//Checking rightwards       
						if(gameCells[i][j].getStatus() == gameCells[i][j+2].getStatus() ){		//horizontal
							if(gameCells[i][j].getStatus() == gameCells[i][j+3].getStatus() ){
								isWinner = 1;
								gameCells[i][j].setWinnerCell(winnerCell);
								gameCells[i][j+1].setWinnerCell(winnerCell);
								gameCells[i][j+2].setWinnerCell(winnerCell);
								gameCells[i][j+3].setWinnerCell(winnerCell);
							}
						}
					}
				}
				if(isWinner != 1){
					if(j>OFFSET-1){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i][j-1].getStatus() ){       	//Checking leftwards       
							if(gameCells[i][j].getStatus() == gameCells[i][j-2].getStatus() ){		//horizontal
								if(gameCells[i][j].getStatus() == gameCells[i][j-3].getStatus() ){
									isWinner = 1;
									gameCells[i][j].setWinnerCell(winnerCell);
									gameCells[i][j-1].setWinnerCell(winnerCell);
									gameCells[i][j-2].setWinnerCell(winnerCell);
									gameCells[i][j-3].setWinnerCell(winnerCell); 
								} 
							}
						}
					}
				}
				if(isWinner != 1){
					if(i<maxHeight-OFFSET){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i+1][j].getStatus() ){       	//Checking downwards       
							if(gameCells[i][j].getStatus() == gameCells[i+2][j].getStatus() ){		//vertical
								if(gameCells[i][j].getStatus() == gameCells[i+3][j].getStatus() ){
									isWinner = 1;
									gameCells[i][j].setWinnerCell(winnerCell);
									gameCells[i+1][j].setWinnerCell(winnerCell);
									gameCells[i+2][j].setWinnerCell(winnerCell);
									gameCells[i+3][j].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i>OFFSET-1){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i-1][j].getStatus() ){       	//Checking upwards       
							if(gameCells[i][j].getStatus() == gameCells[i-2][j].getStatus() ){		//vertical
								if(gameCells[i][j].getStatus() == gameCells[i-3][j].getStatus() ){
									isWinner = 1;
									gameCells[i][j].setWinnerCell(winnerCell);
									gameCells[i-1][j].setWinnerCell(winnerCell);
									gameCells[i-2][j].setWinnerCell(winnerCell);
									gameCells[i-3][j].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i>OFFSET-1 && j<maxWidth - OFFSET){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i-1][j+1].getStatus() ){       	//Top-Right      
							if(gameCells[i][j].getStatus() == gameCells[i-2][j+2].getStatus() ){		//Diagonal
								if(gameCells[i][j].getStatus() == gameCells[i-3][j+3].getStatus() ){
									isWinner = 1;
									gameCells[i][j].setWinnerCell(winnerCell);
									gameCells[i-1][j+1].setWinnerCell(winnerCell);
									gameCells[i-2][j+2].setWinnerCell(winnerCell);
									gameCells[i-3][j+3].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i-1][j-1].getStatus() ){       	//Top-Left     
							if(gameCells[i][j].getStatus() == gameCells[i-2][j-2].getStatus() ){		//Diagonal
								if(gameCells[i][j].getStatus() == gameCells[i-3][j-3].getStatus() ){
									isWinner = 1;
									gameCells[i][j].setWinnerCell(winnerCell);
									gameCells[i-1][j-1].setWinnerCell(winnerCell);
									gameCells[i-2][j-2].setWinnerCell(winnerCell);
									gameCells[i-3][j-3].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i<maxHeight - OFFSET && j<maxWidth - OFFSET){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i+1][j+1].getStatus() ){       	//Bottom-Right      
							if(gameCells[i][j].getStatus() == gameCells[i+2][j+2].getStatus() ){		//Diagonal
								if(gameCells[i][j].getStatus() == gameCells[i+3][j+3].getStatus() ){
									isWinner = 1;
									gameCells[i][j].setWinnerCell(winnerCell);
									gameCells[i+1][j+1].setWinnerCell(winnerCell);
									gameCells[i+2][j+2].setWinnerCell(winnerCell);
									gameCells[i+3][j+3].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i<maxHeight - OFFSET && j>OFFSET-1){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i+1][j-1].getStatus() ){       	//Bottom-Left     
							if(gameCells[i][j].getStatus() == gameCells[i+2][j-2].getStatus() ){		//Diagonal
								if(gameCells[i][j].getStatus() == gameCells[i+3][j-3].getStatus() ){
									isWinner = 1;
									gameCells[i][j].setWinnerCell(winnerCell);
									gameCells[i+1][j-1].setWinnerCell(winnerCell);
									gameCells[i+2][j-2].setWinnerCell(winnerCell);
									gameCells[i+3][j-3].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
			}
		}
	}	
	return isWinner;
}




void ConnectFour::play(int move){
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






void ConnectFour::play(){
	int isMadeMove = 0; //0 If bot haven't made a move yet.
	const int OFFSET = 3; //Offset for checking board Vertical/Horizontal
	const int isAI = 1;   // Parameter for checkIllegalMove function to ignore illegal move err for AI.

	int moveI = -1;		//Coordinates of move
	int moveJ = -1;		//If these stay as -1 there's no lose threat in the game
	//AI Checks if there's a winning move
		for(int i=0; i<maxHeight; ++i){   //i stands for rows
			for(int j=0; j<maxWidth; ++j){ //j stands for columns
				if(gameCells[i][j].getStatus() == "Computer"){ //Checks if there's his token	
					if(j<maxWidth-OFFSET){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i][j+1].getStatus()){       	//Checking rightwards       
							if(gameCells[i][j].getStatus() == gameCells[i][j+2].getStatus()){		//horizontal
								if(gameCells[i][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+1][j+3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i][j-1].getStatus()){       	//Checking leftwards       
							if(gameCells[i][j].getStatus() == gameCells[i][j-2].getStatus()){		//horizontal
								if(gameCells[i][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+1][j-3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i+1][j].getStatus()){       	//Checking downwards       
							if(gameCells[i][j].getStatus() == gameCells[i+2][j].getStatus()){		//vertical
								if(gameCells[i+3][j].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+3+1][j].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i-1][j].getStatus()){       	//Checking upwards       
							if(gameCells[i][j].getStatus() == gameCells[i-2][j].getStatus()){		//vertical
								if(gameCells[i-3][j].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i-3+1][j].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i-1][j+1].getStatus()){       	//Top-Right      
							if(gameCells[i][j].getStatus() == gameCells[i-2][j+2].getStatus()){		//Diagonal
								if(gameCells[i-3][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[-3+1][j+3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i-1][j-1].getStatus()){       	//Top-Left     
							if(gameCells[i][j].getStatus() == gameCells[i-2][j-2].getStatus()){		//Diagonal
								if(gameCells[i-3][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i-3+1][j-3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i+1][j+1].getStatus()){       	//Bottom-Right      
							if(gameCells[i][j].getStatus() == gameCells[i+2][j+2].getStatus()){		//Diagonal
								if(gameCells[i+3][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+3+1][j+3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i+1][j-1].getStatus()){       	//Bottom-Left     
							if(gameCells[i][j].getStatus() == gameCells[i+2][j-2].getStatus()){		//Diagonal
								if(gameCells[i+3][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+3+1][j-3].getStatus() != "Empty"){
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
				if(gameCells[i][j].getStatus() == "User1"){ //Checks if it's enemy token		
					if(j<maxWidth-OFFSET){ //Preventing overflow
						if(gameCells[i][j].getStatus() == gameCells[i][j+1].getStatus()){       	//Checking rightwards       
							if(gameCells[i][j].getStatus() == gameCells[i][j+2].getStatus()){		//horizontal
								if(gameCells[i][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+1][j+3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i][j-1].getStatus()){       	//Checking leftwards       
							if(gameCells[i][j].getStatus() == gameCells[i][j-2].getStatus()){		//horizontal
								if(gameCells[i][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+1][j-3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i+1][j].getStatus()){       	//Checking downwards       
							if(gameCells[i][j].getStatus() == gameCells[i+2][j].getStatus()){		//vertical
								if(gameCells[i+3][j].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+3+1][j].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i-1][j].getStatus()){       	//Checking upwards       
							if(gameCells[i][j].getStatus() == gameCells[i-2][j].getStatus()){		//vertical
								if(gameCells[i-3][j].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i-3+1][j].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i-1][j+1].getStatus()){       	//Top-Right      
							if(gameCells[i][j].getStatus() == gameCells[i-2][j+2].getStatus()){		//Diagonal
								if(gameCells[i-3][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i-3+1][j+3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i-1][j-1].getStatus()){       	//Top-Left     
							if(gameCells[i][j].getStatus() == gameCells[i-2][j-2].getStatus()){		//Diagonal
								if(gameCells[i-3][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i-3][j-3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i+1][j+1].getStatus()){       	//Bottom-Right      
							if(gameCells[i][j].getStatus() == gameCells[i+2][j+2].getStatus()){		//Diagonal
								if(gameCells[i+3][j+3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+3+1][j+3].getStatus() != "Empty"){
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
						if(gameCells[i][j].getStatus() == gameCells[i+1][j-1].getStatus()){       	//Bottom-Left     
							if(gameCells[i][j].getStatus() == gameCells[i+2][j-2].getStatus()){		//Diagonal
								if(gameCells[i+2][j-3].getStatus() == "Empty"){
									if(i < maxHeight -1){
										if(gameCells[i+3+1][j-3].getStatus() != "Empty"){
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


