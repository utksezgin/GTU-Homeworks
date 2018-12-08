//Azmi Utku Sezgin 131044048 HW02

#include <iostream>
#include <string> //String Functions
#include <stdlib.h>//Included to create a random number with srand/rand
#include <time.h>  //Same as stdlib.h time()
#include <math.h> //Pow function
#include <fstream> //Read/Write files
using namespace std;

void play();
void printBoard(char **board, int boardSize); //Prints current board
void initializeBoard(char **board, int boardSize); //Fills the board with '.' chars
int checkWinner(char **board, int boardSize); //Checks if there's a winner or game is draw
void makeMove(char **board, int boardSize, char token, int column); //Changes board according to move
void computerMove(char **board, int boardSize);//Makes the play for computer
int checkIllegalMove(char **board, int boardSize, int column, int isAI = 0); //Returns -1 if the move is illegal
int charToInt(char c);//Works for a-t and A-T in alphabet.
int stringToInt(string str); //Converts string to an integer
char upperToLower(char letter); //Converts upper case to lower
void saveToFile(char **board, int boardSize, const string saveFile, const int &isAI,const int &whosTurn);//Saves the game to the text file. ***This function creates only 1 line of text.
char** loadFromFile(char **&board, int &boardSize, const string loadFile, int  &isAI, int &whosTurn);//Loads the game from the text file returns new board
int checkCommand(char **board, int boardSize, int column, int isAI, string input); //Returns 0 for save, 1 for load, 2 for proper move command and -1 for unkown commands
void realloc (char**& a, size_t size, size_t newsize); //Reallocates the allocated memory.


int main(){
 	play();
	return 0;
	
}


void play(){
	const int firstFive = 5; //In order to skip 5 from input ("LOAD " and "SAVE ")
	string input; 
	int whosTurn =1; //1 for player 1's turn 2 for player 2's turn.
	int boardSize = 0;
	auto isProper = 0;
	decltype(isProper) isAI = 0;
	const int notAI = 0; //Parameter that player's move sends to checkIllegalMove as an argumant
	string buffer;
	
	while(isProper == 0 && boardSize != -1)
	{
		cout << "Please enter the board size an even number between 4-20" << endl;
		cin >> input;
		boardSize = stringToInt(input);
		if(boardSize ==-1)
			isProper = 0;
		else
			isProper = 1;	
		if((boardSize%2!= 0 || boardSize >20 || boardSize <4) && boardSize != -1){
			cerr << "Wrong input" << endl;
			isProper=0;
			cin.clear();
		}
	}
	
	//Allocating memory for the board
	char **Board = new char*[boardSize];
	for(int i = 0; i<boardSize ; ++i)
		Board[i] = new char[boardSize];
		
	//Initializing the board
	initializeBoard(Board, boardSize);
	
		
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
	
	printBoard(Board, boardSize);
	
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
			commandNo = checkCommand(Board, boardSize, moveColumn, isAI, command);
			switch (commandNo) {
				case 0:
					//Getting fileName from Load Command
					if( command.length() > firstFive){
					for(int k=firstFive, i=0; k<command.length(); ++k, ++i)
						fileName[i] = command[k];
						saveToFile(Board, boardSize, fileName, isAI, whosTurn);
					}
					else
						cerr << "Unknown input. Couldn't find the file name" << endl;
					break;
				case 1:
					//Getting fileName from Load Command
					if( command.length() > firstFive){
						for(int k=firstFive,  i=0; k<command.length(); ++k, ++i)
							fileName[i] = command[k];
						Board = loadFromFile(Board, boardSize, fileName, isAI, whosTurn);
					}
					else
						cerr << "Unknown input. Couldn't find the file name" << endl;
					break;
				case 2:
					if( command.length() == 1){
						isProper = 1;
						moveColumn = charToInt(command[0]);
						makeMove(Board, boardSize, 'X', moveColumn);
						whosTurn = 2;
						printBoard(Board, boardSize);
						lastMove = 1;
						isGameOver = checkWinner(Board, boardSize);
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
				computerMove(Board, boardSize);
				printBoard(Board, boardSize);
				whosTurn = 1;
				lastMove = 2;
			}			
			else{
				isProper = -1;
				while( isProper == -1){
					cout << "Player 2's Turn, Make your move." << endl << endl;
					cin.clear();
					getline(std::cin, command);
					commandNo = checkCommand(Board, boardSize, moveColumn, isAI, command);
					switch (commandNo) {
						case 0:
							//Getting fileName from Load Command
							if( command.length() > firstFive){
								for(int k=firstFive, i=0; k<command.length(); ++k, ++i)
									fileName[i] = command[k];
									saveToFile(Board, boardSize, fileName, isAI, whosTurn);
							}
							else
								cerr << "Unknown input. Couldn't find the file name" << endl;
							break;
						case 1:
							//Getting fileName from Load Command
							if( command.length() > firstFive){
								for(int k=firstFive, i=0; k<command.length(); ++k, ++i)
									fileName[i] = command[k];
									Board = loadFromFile(Board, boardSize, fileName, isAI, whosTurn);
							}
							else
								cerr << "Unknown input. Couldn't find the file name" << endl;
							break;
						case 2:
							if(command.length() == 1){
								isProper = 1;
								moveColumn = charToInt(command[0]);
								makeMove(Board, boardSize, 'O', moveColumn);
								whosTurn = 1;
								printBoard(Board, boardSize);
								lastMove = 1;
								isGameOver = checkWinner(Board, boardSize);
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
			isGameOver = checkWinner(Board, boardSize);
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
	
	printBoard(Board, boardSize); //Printing the final board
	
	//Deallocating memory of board
	for(int i=0; i < boardSize; ++i)
		delete [] Board[i];
	delete[] Board;
	Board = 0;
	

}
void initializeBoard(char **board, int boardSize){	
	for(int i = 0; i<boardSize; ++i){
		for(int j = 0; j<boardSize; ++j){
			board[i][j] = '.';
		}
	}
}

void printBoard(char **board, int boardSize){
	char column = 'a';
	for(int i = 0; i<boardSize; ++i){
		cout << column;
		++column;
	}
	
	cout << endl;
	
	for(int i = 0; i<boardSize; ++i){
		for(int j = 0; j<boardSize; ++j){
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

int charToInt(char c){
	int col;
	if(c<85 && c>64)
		col = c-65;
	else if(c<117 && c>96)
		col = c-97;
	else
		col = -1;
	return col;
}

int checkIllegalMove(char **board, int boardSize, int column, int isAI){
	int isIllegal =-1;
	if(boardSize > column){
		for(int i=boardSize-1; i>=0; --i){
			if(board[i][column] == '.')
				isIllegal = 1;
		}
	}
	if(isIllegal == -1 && isAI == 0)
		cerr << "Unknown Command" << endl;
	return isIllegal;		
}

void makeMove(char **board, int boardSize, char token, int column){
	int row = 0;
	for(int i=boardSize-1; i>-1; --i){
		if(board[i][column] == '.'){
			row = i;
			i = -1;
		}
	}
	board[row][column]=token;
}


int checkWinner(char **board, int boardSize){
	const int OFFSET = 3;
	int isWinner = 2; //Set to 2 by default. 2 Stands for draw.
	//Checking for Draw.
	for(int i=0; i<boardSize; ++i){   //i stands for rows
		for(int j=0; j<boardSize; ++j){ //j stands for columns
			if(board[i][j] == '.'){ //If there's an empty cell, it's not draw
				isWinner = -1;
			}
		}
	}
	
	for(int i=0; i<boardSize; ++i){   //i stands for rows
		for(int j=0; j<boardSize; ++j){ //j stands for columns
			if(board[i][j] != '.'){ //Checks if that cell is empty			
				if(j<boardSize-OFFSET){ //Preventing overflow
					if(board[i][j] == board[i][j+1]){       	//Checking rightwards       
						if(board[i][j] == board[i][j+2]){		//horizontal
							if(board[i][j] == board[i][j+3]){
								isWinner = 1;
								board[i][j] = upperToLower(board[i][j]);  	  //
								board[i][j+1] = upperToLower(board[i][j+1]);  //Converting upper case letters
								board[i][j+2] = upperToLower(board[i][j+2]);  //to lower cases
								board[i][j+3] = upperToLower(board[i][j+3]);  //
							}
						}
					}
				}
				if(isWinner != 1){
					if(j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i][j-1]){       	//Checking leftwards       
							if(board[i][j] == board[i][j-2]){		//horizontal
								if(board[i][j] == board[i][j-3]){
									isWinner = 1;
									board[i][j] = upperToLower(board[i][j]); 
									board[i][j-1] = upperToLower(board[i][j-1]);
									board[i][j-2] = upperToLower(board[i][j-2]);
									board[i][j-3] = upperToLower(board[i][j-3]); 
								} 
							}
						}
					}
				}
				if(isWinner != 1){
					if(i<boardSize-OFFSET){ //Preventing overflow
						if(board[i][j] == board[i+1][j]){       	//Checking downwards       
							if(board[i][j] == board[i+2][j]){		//vertical
								if(board[i][j] == board[i+3][j]){
									isWinner = 1;
									board[i][j] = upperToLower(board[i][j]); 
									board[i+1][j] = upperToLower(board[i+1][j]);
									board[i+2][j] = upperToLower(board[i+2][j]);
									board[i+3][j] = upperToLower(board[i+3][j]);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i-1][j]){       	//Checking upwards       
							if(board[i][j] == board[i-2][j]){		//vertical
								if(board[i][j] == board[i-3][j]){
									isWinner = 1;
									board[i][j] = upperToLower(board[i][j]); 
									board[i-1][j] = upperToLower(board[i-1][j]);
									board[i-2][j] = upperToLower(board[i-2][j]);
									board[i-3][j] = upperToLower(board[i-3][j]);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i>OFFSET-1 && j<boardSize - OFFSET){ //Preventing overflow
						if(board[i][j] == board[i-1][j+1]){       	//Top-Right      
							if(board[i][j] == board[i-2][j+2]){		//Diagonal
								if(board[i][j] == board[i-3][j+3]){
									isWinner = 1;
									board[i][j] = upperToLower(board[i][j]); 
									board[i-1][j+1] = upperToLower(board[i-1][j+1]);
									board[i-2][j+2] = upperToLower(board[i-2][j+2]);
									board[i-3][j+3] = upperToLower(board[i-3][j+3]);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i-1][j-1]){       	//Top-Left     
							if(board[i][j] == board[i-2][j-2]){		//Diagonal
								if(board[i][j] == board[i-3][j-3]){
									isWinner = 1;
									board[i][j] = upperToLower(board[i][j]); 
									board[i-1][j-1] = upperToLower(board[i-1][j-1]);
									board[i-2][j-2] = upperToLower(board[i-2][j-2]);
									board[i-3][j-3] = upperToLower(board[i-3][j-3]);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i<boardSize - OFFSET && j<boardSize - OFFSET){ //Preventing overflow
						if(board[i][j] == board[i+1][j+1]){       	//Bottom-Right      
							if(board[i][j] == board[i+2][j+2]){		//Diagonal
								if(board[i][j] == board[i+3][j+3]){
									isWinner = 1;
									board[i][j] = upperToLower(board[i][j]); 
									board[i+1][j+1] = upperToLower(board[i+1][j+1]);
									board[i+2][j+2] = upperToLower(board[i+2][j+2]);
									board[i+3][j+3] = upperToLower(board[i+3][j+3]);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i<boardSize - OFFSET && j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i+1][j-1]){       	//Bottom-Left     
							if(board[i][j] == board[i+2][j-2]){		//Diagonal
								if(board[i][j] == board[i+3][j-3]){
									isWinner = 1;
									board[i][j] = upperToLower(board[i][j]); 
									board[i+1][j-1] = upperToLower(board[i+1][j-1]);
									board[i+2][j-2] = upperToLower(board[i+2][j-2]);
									board[i+3][j-3] = upperToLower(board[i+3][j-3]);
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




void computerMove(char **board, int boardSize){

	int isMadeMove = 0; //0 If bot haven't made a move yet.
	const int OFFSET = 3; //Offset for checking board Vertical/Horizontal
	const int isAI = 1;   // Parameter for checkIllegalMove function to ignore illegal move err for AI.
	
	int moveI = -1;		//Coordinates of move
	int moveJ = -1;		//If these stay as -1 there's no lose threat in the game
	//AI Checks if there's a winning move
		for(int i=0; i<boardSize; ++i){   //i stands for rows
			for(int j=0; j<boardSize; ++j){ //j stands for columns
				if(board[i][j] == 'O'){ //Checks if there's his token	
					if(j<boardSize-OFFSET){ //Preventing overflow
						if(board[i][j] == board[i][j+1]){       	//Checking rightwards       
							if(board[i][j] == board[i][j+2]){		//horizontal
								if(board[i][j+3] == '.'){
									if(i < boardSize -1){
										if(board[i+1][j+3] != '.'){
											moveI = i;
											moveJ = j+3;
										}
									}
									else if( i == boardSize -1){
										moveI = i;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i][j-1]){       	//Checking leftwards       
							if(board[i][j] == board[i][j-2]){		//horizontal
								if(board[i][j-3] == '.'){
									if(i < boardSize -1){
										if(board[i+1][j-3] != '.'){
											moveI = i;
											moveJ = j-3;
										}
									}
									else if( i == boardSize -1){
										moveI = i;
										moveJ = j-3;
									}
								}
							}
						}
					}
					if(i<boardSize-OFFSET){ //Preventing overflow
						if(board[i][j] == board[i+1][j]){       	//Checking downwards       
							if(board[i][j] == board[i+2][j]){		//vertical
								if(board[i+3][j] == '.'){
									if(i < boardSize -1){
										if(board[i+3+1][j] != '.'){
											moveI = i+3;
											moveJ = j;
										}
									}
									else if( i == boardSize -1){
										moveI = i+3;
										moveJ = j;
									}
								}
							}
						}
					}
					if(i>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i-1][j]){       	//Checking upwards       
							if(board[i][j] == board[i-2][j]){		//vertical
								if(board[i-3][j] == '.'){
									if(i < boardSize -1){
										if(board[i-3+1][j] != '.'){
											moveI = i-3;
											moveJ = j;
										}
									}
									else if( i == boardSize -1){
										moveI = i-3;
										moveJ = j;
									}
								}
							}
						}
					}
					if(i>OFFSET-1 && j<boardSize - OFFSET){ //Preventing overflow
						if(board[i][j] == board[i-1][j+1]){       	//Top-Right      
							if(board[i][j] == board[i-2][j+2]){		//Diagonal
								if(board[i-3][j+3] == '.'){
									if(i < boardSize -1){
										if(board[i-3+1][j+3] != '.'){
											moveI = i-3;
											moveJ = j+3;
										}
									}
									else if( i == boardSize -1){
										moveI = i-3;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i-1][j-1]){       	//Top-Left     
							if(board[i][j] == board[i-2][j-2]){		//Diagonal
								if(board[i-3][j-3] == '.'){
									if(i < boardSize -1){
										if(board[i-3+1][j-3] != '.'){
											moveI = i-3;
											moveJ = j-3;
										}
									}
									else if( i == boardSize -1){
										moveI = i-3;
										moveJ = j-3;
									}
								}
							}
						}
					}
					if(i<boardSize - OFFSET && j<boardSize - OFFSET){ //Preventing overflow
						if(board[i][j] == board[i+1][j+1]){       	//Bottom-Right      
							if(board[i][j] == board[i+2][j+2]){		//Diagonal
								if(board[i+3][j+3] == '.'){
									if(i < boardSize -1){
										if(board[i+3+1][j+3] != '.'){
											moveI = i+3;
											moveJ = j+3;
										}
									}
									else if( i == boardSize -1){
										moveI = i+3;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(i<boardSize - OFFSET && j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i+1][j-1]){       	//Bottom-Left     
							if(board[i][j] == board[i+2][j-2]){		//Diagonal
								if(board[i+3][j-3] == '.'){
									if(i < boardSize -1){
										if(board[i+3+1][j-3] != '.'){
											moveI = i+3;
											moveJ = j-3;
										}
									}
									else if( i == boardSize -1){
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
		makeMove(board, boardSize, 'O', moveJ);
		isMadeMove = 1;
	}
	else if( isMadeMove == 0){ //If there's no losing threat, AI makes it's own move 
	
	//int moveI = -1;		//Setting them to -1 again
	//int moveJ = -1;		//in order to prevent Computer make multiple moves
	//Checks if the enemy has a winning move
		for(int i=0; i<boardSize; ++i){   //i stands for rows
			for(int j=0; j<boardSize; ++j){ //j stands for columns
				if(board[i][j] == 'X'){ //Checks if it's enemy token		
					if(j<boardSize-OFFSET){ //Preventing overflow
						if(board[i][j] == board[i][j+1]){       	//Checking rightwards       
							if(board[i][j] == board[i][j+2]){		//horizontal
								if(board[i][j+3] == '.'){
									if(i < boardSize -1){
										if(board[i+1][j+3] != '.'){
											moveI = i;
											moveJ = j+3;
										}
									}
									else if( i == boardSize -1){
										moveI = i;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i][j-1]){       	//Checking leftwards       
							if(board[i][j] == board[i][j-2]){		//horizontal
								if(board[i][j-3] == '.'){
									if(i < boardSize -1){
										if(board[i+1][j-3] != '.'){
											moveI = i;
											moveJ = j-3;
										}
									}
									else if( i == boardSize -1){
										moveI = i;
										moveJ = j-3;
									}
								}
							}
						}
					}
					if(i<boardSize-OFFSET){ //Preventing overflow
						if(board[i][j] == board[i+1][j]){       	//Checking downwards       
							if(board[i][j] == board[i+2][j]){		//vertical
								if(board[i+3][j] == '.'){
									if(i < boardSize -1){
										if(board[i+3+1][j] != '.'){
											moveI = i+3;
											moveJ = j;
										}
									}
									else if( i == boardSize -1){
										moveI = i+3;
										moveJ = j;
									}
								}
							}
						}
					}
					if(i>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i-1][j]){       	//Checking upwards       
							if(board[i][j] == board[i-2][j]){		//vertical
								if(board[i-3][j] == '.'){
									if(i < boardSize -1){
										if(board[i-3+1][j] != '.'){
											moveI = i-3;
											moveJ = j;
										}
									}
									else if( i == boardSize -1){
										moveI = i-3;
										moveJ = j;
									}
								}
							}
						}
					}
					if(i>OFFSET-1 && j<boardSize - OFFSET){ //Preventing overflow
						if(board[i][j] == board[i-1][j+1]){       	//Top-Right      
							if(board[i][j] == board[i-2][j+2]){		//Diagonal
								if(board[i-3][j+3] == '.'){
									if(i < boardSize -1){
										if(board[i-3+1][j+3] != '.'){
											moveI = i-3;
											moveJ = j+3;
										}
									}
									else if( i == boardSize -1){
										moveI = i-3;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i-1][j-1]){       	//Top-Left     
							if(board[i][j] == board[i-2][j-2]){		//Diagonal
								if(board[i-3][j-3] == '.'){
									if(i < boardSize -1){
										if(board[i-3+1][j-3] != '.'){
											moveI = i-3;
											moveJ = j-3;
										}
									}
									else if( i == boardSize -1){
										moveI = i-3;
										moveJ = j-3;
									}
								}
							}
						}
					}
					if(i<boardSize - OFFSET && j<boardSize - OFFSET){ //Preventing overflow
						if(board[i][j] == board[i+1][j+1]){       	//Bottom-Right      
							if(board[i][j] == board[i+2][j+2]){		//Diagonal
								if(board[i+3][j+3] == '.'){
									if(i < boardSize -1){
										if(board[i+3+1][j+3] != '.'){
											moveI = i+3;
											moveJ = j+3;
										}
									}
									else if( i == boardSize -1){
										moveI = i+3;
										moveJ = j+3;
									}
								}
							}
						}
					}
					if(i<boardSize - OFFSET && j>OFFSET-1){ //Preventing overflow
						if(board[i][j] == board[i+1][j-1]){       	//Bottom-Left     
							if(board[i][j] == board[i+2][j-2]){		//Diagonal
								if(board[i+3][j-3] == '.'){
									if(i < boardSize -1){
										if(board[i+3+1][j-3] != '.'){
											moveI = i+3;
											moveJ = j-3;
										}
									}
									else if( i == boardSize -1){
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
		if( checkIllegalMove(board, boardSize, moveJ, isAI) ){
			makeMove(board, boardSize, 'O', moveJ);
		}
	}
	else if( isMadeMove == 0){ //There's no winning or blocking move so Computer makes a random move.
		int randomColumn;
		int isIllegal;
		do{
			srand (time(NULL));
			randomColumn = rand() % boardSize;
			isIllegal = checkIllegalMove(board, boardSize, randomColumn, isAI);
		}
		while(isIllegal != 1);
		makeMove(board, boardSize, 'O', randomColumn);	
	}
	
}
		
		
int stringToInt(string str){
	int number=0;
	for(int i=0; i<str.length(); ++i){
		number+= ( (str[i]-'0') * pow(10, (str.length()-i-1) ));
	}
	return number;
}

char upperToLower(char letter){
	char upperCase;
	upperCase = letter + 32;
	return upperCase;
}

void saveToFile(char **board, int boardSize,const string saveFile, const int &isAI,const int &whosTurn){
	ofstream saveF;
	
	saveF.open(saveFile.c_str());//Opening text file
	
	if( saveF.is_open() ){ //Checking if file is open successfully
		saveF << boardSize << " " << isAI << " " << whosTurn << " "; //Saving boardSize, isAI, isGameOver
		
		for(int i=0; i<boardSize; ++i){ //Saving board
			for(int j=0; j<boardSize; ++j){	
				saveF << board[i][j];
			}			
		}
		cout << "Game is successfully saved!" << endl; 
	}
	else
		cerr << "Couldn't open the file" << endl;
	
	saveF.close(); //Closing the file
}

char** loadFromFile(char **&board, int &boardSize,const string loadFile, int  &isAI, int &whosTurn){
	fstream loadF;
	string line; //The line that we read from save file
	string temp; //Temp string for parsing
	int oldBoardSize = boardSize;
	
	
	loadF.open(loadFile.c_str(), std::fstream::in);//Opening text file
	
	if( loadF.is_open() ){
		while ( getline (loadF,line) );//Reading the line from savefile
		
		int i=0;
		if(line.length() < 1)
			cerr << "Corrupted save file" << endl;
		else{
			while(line[i] != ' '){ //Reading boardSize from line string
				temp += line[i];
				++i;
			}
			boardSize = stringToInt(temp);
			++i; //Skipping empty cell
			temp.clear(); //Clearing temp string
			temp.resize(1);
	
			while(line[i] != ' '){ //Reading isAI from line string
				temp[0] = line[i];
				++i;
			}
			isAI = stringToInt(temp);
			++i; //Skipping empty cell 
			temp.clear(); //Clearing temp string
			temp.resize(1);
			
			while(line[i] != ' '){ //Reading whosTurn from line string
				temp[0] = line[i];
				++i;
			}
			whosTurn = stringToInt(temp);
			++i; //Skipping empty cell 
			temp.clear(); //Clearing temp string
			//Reallocating memory of old board			
			realloc(board, oldBoardSize, boardSize);
			
			//Reading board from line string
			int j=0, k=0;
			while( i<line.length() && k< boardSize && j < boardSize){
				board[j][k] = line[i];
				++k;
				if(k == boardSize){
					k = 0;
					++j;
				}
				++i;
			}
			cout << "Game successfully loaded" << endl;
			printBoard(board, boardSize);
		}		
		return board;
	}
	else{
		cerr << "Couldn't open the file" << endl;
		return board;
	}		
		
	loadF.close();	
	
}

int checkCommand(char **board, int boardSize, int column, int isAI, string input){
	if( (input[0]=='S' && input[1]=='A' && input[2]=='V' && input[3]=='E') || (input[0]=='s' && input[1]=='a' && input[2]=='v' && input[3]=='e') )
		return 0;
	else if( (input[0]=='L' && input[1]=='O' && input[2]=='A' && input[3]=='D') || (input[0]=='l' && input[1]=='o' && input[2]=='a' && input[3]=='d') )
		return 1;
	else if( checkIllegalMove(board, boardSize, charToInt(input[0]), isAI) == 1)
		return 2;
	else
		return -1;
}

void realloc (char**& a, size_t size, size_t newsize) {
  for(int i = 0; i < size; ++i)
    delete [] a[i];
  delete [] a;

  size = newsize;
  a = new char* [size];
  for (int i = 0; i < size; ++i)
    a[i] = new char [size];
}
