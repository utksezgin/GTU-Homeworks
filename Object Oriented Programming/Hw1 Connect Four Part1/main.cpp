//Azmi Utku Sezgin 131044048 HW01

#include <iostream>
#include <string> //String Functions
#include <stdlib.h>//Included to create a random number with srand/rand
#include <time.h>  //Same as stdlib.h time()
#include <math.h> //Pow function
using namespace std;

void play();
void printBoard(char **board, int boardSize); //Prints current board
void initializeBoard(char **board, int boardSize); //Fills the board with '.' chars
int checkWinner(char **board, int boardSize); //Checks if there's a winner or game is draw
void makeMove(char **board, int boardSize, char token, int column); //Changes board according to move
void computerMove(char **board, int boardSize);//Makes the play for computer
int checkIllegalMove(char **board, int boardSize, int columni, int isAI); //Returns -1 if the move is illegal
int charToInt(char c);//Works for a-t and A-T in alphabet.
int stringToInt(string str); //Converts string to an integer
char upperToLower(char letter); //Converts upper case to lower


int main(){
 	play();
	return 0;
	
}


void play(){
	string input;
	int boardSize = 0;
	int isProper = 0;
	int isAI = 0;
	const int notAI = 0; //Parameter that player's move sends to checkIllegalMove as an argumant
	
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
		
	printBoard(Board, boardSize);
	
	int lastMove =0; // If last move is made by 1st player it's 1 if 2nd player it's 2
	char playersMove;
	int moveColumn;
	int isGameOver = -1;
	while(isGameOver == -1){
	
		isProper = -1;
		while( isProper == -1){
			cout << "Player 1's Turn, Make your move." << endl << endl;
			cin >> playersMove;
			moveColumn = charToInt(playersMove);
			isProper = checkIllegalMove(Board, boardSize, moveColumn, notAI);
		}
		makeMove(Board, boardSize, 'X', moveColumn);
		printBoard(Board, boardSize);
		lastMove = 1;
		isGameOver = checkWinner(Board, boardSize);
		
		if(isGameOver == -1){
			if(isAI == 1){
				cout << "Comptuer's Turn." << endl << endl;
				computerMove(Board, boardSize);
				printBoard(Board, boardSize);
			}			
			else{
				isProper = -1;
				while( isProper == -1){
					cout << "Player 2's Turn, Make your move." << endl << endl;
					cin >> playersMove;
					moveColumn = charToInt(playersMove);
					isProper = checkIllegalMove(Board, boardSize, moveColumn, isAI);
				}
				makeMove(Board, boardSize, 'O', moveColumn);
				printBoard(Board, boardSize);
			}
			lastMove = 2;
			isGameOver = checkWinner(Board, boardSize);
		}
	}
	
	if(isGameOver == 1){
		if(isAI == 1)
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
		cerr << "This move is illegal" << endl;
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

