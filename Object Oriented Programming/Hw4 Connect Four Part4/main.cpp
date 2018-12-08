//Azmi Utku Sezgin 131044048 HW04

#include <iostream>
#include <string> //String Functions
#include <stdlib.h>//Included to create a random number with srand/rand
#include <time.h>  //Same as stdlib.h time()
#include <math.h> //Pow function
#include <fstream> //Read/Write files
#include "Cell.h"	//Cell Class
#include "ConnectFour.h" //ConnectFour Class
#include <fstream> //Read/Write files
using namespace std;

int main(){
	//ConnectFour file("save3.txt"); //Constructor works with filename
	string fileName;
	char singleOrMulti;
	char properInput = 0;
	int maxHeight = 0; //Temporary variables to use on 
	int maxWidth = 0; //ConnectFour::resizeBoard function
	const int MIN_GAME = 2; //Minimum game amount a player can play at the same time except for singleplay.
	const int MAX_GAME = 10; //Maximum game amount a player can play at the same time.
	const int MIN_HEIGHT = 4; //Minimum board height
	const int MIN_WIDTH = 4; //Minimum board width
	const int MAX_HEIGHT = 50; //Maximum board height
	const int MAX_WIDTH = 26; //Maximum board width
	
	cout << "Welcome to Connect Four! Please enter 'S' for playing on 1 game or 'M' to play multiple games";
	cout << " at the same time" << endl;
	while(properInput == 0){
		cin >> singleOrMulti;
		if(singleOrMulti == 'S' || singleOrMulti == 's'){
			singleOrMulti = 'S';
			properInput = 1;
		}
		else if(singleOrMulti == 'M' || singleOrMulti == 'm'){
			singleOrMulti = 'M';
			properInput = 1;
		}
		else{
			properInput =0;
			cerr << "Unknown input, Please enter 'S' or 'M' to start the game" << endl;
		}
	}
	if(singleOrMulti =='S'){
		ConnectFour singleGame;
		singleGame.playGame();
	}
	else{
		int gameCount =0;
		cout << "Please enter how many games would you like to play at the same time Min:2 Max:10" << endl;
		properInput = 0;
		while(properInput == 0){
			cin >> gameCount;
			if(gameCount < MIN_GAME || gameCount > MAX_GAME){
				cerr << "The number must be greater than 2 and less than 100" << endl;
				cin.clear();
			}
			else{
				properInput = 1;
				cin.clear();
			}
		}
		vector<ConnectFour> multiGame(gameCount);
		
		
		string input;
		int number;
		for(int i=0; i< gameCount; ++i){
			cout << "Please enter a filename for your board" << endl;
			cin.clear();
			cin >> fileName;
			if(fileName.length() == 0 || cin.eof() ){ //EoF Check
				cerr << "End of file" << endl;
				exit(0);
			}
					
			//Resizing board
			multiGame[i].readBoard(fileName);
			
			
			properInput = 0;
			char userChoice;			
			while(properInput == 0){
				cout << "Please enter 'C' for playing against the computer or 'P' for playing against a player" << endl;
				cin.ignore();
				cin >> userChoice;
				if(userChoice == 'c' || userChoice == 'C'){
					multiGame[i].setIsAI(1);
					properInput = 1;
				}
				else if(userChoice == 'P' || userChoice == 'p'){
					properInput =1 ;
					multiGame[i].setIsAI(0);
				}
			}
			cin.ignore();						
		}
		
		
		int gameNotOver = 1; //0 if the game is over
		int objectNo = 0; //Objcets number to play
		input.clear();
		
		while(gameNotOver == 1){
		
			//Checking if the games are over
			gameNotOver = 0;
			for(int i=0; i<gameCount; ++i){
				if(multiGame[i].getIsGameOver() == 0){
					gameNotOver = 1;
				}
			}
			
			cout << "Is object 1 equal to object 0? " << ( multiGame[0] == multiGame[1] ) << endl;
			cout << "Is object 1 not equal to object 0? " << ( multiGame[0] != multiGame[1] ) << endl;
			if(gameNotOver == 1){
				//Getting an object number from the user
				properInput = 0;
				while(properInput == 0){
					cout << "Choose an object from 1 to " << gameCount << endl;
					cin.clear();
					cin >> input;
					if(input.length() == 0 || cin.eof()){ //EoF Check
						cerr << "End of file" << endl;
						exit(0);
					}
					objectNo = multiGame[0].stringToInt(input);
				 	if(objectNo >= 1 && objectNo <= gameCount){
				 		if( multiGame[objectNo-1].getIsGameOver() == 1 || multiGame[objectNo-1].getIsGameOver() == 2 )
				 			cerr << "This game is already over, pick another game" << endl;
						else
							properInput = 1;			 			
					}
					else{
						cerr << "Unknown Object" << endl;
					} 
				}
				
				cin.ignore();
	
				multiGame[objectNo-1].printBoard();
				const int firstFive = 5; //Skipping "LOAD ", "SAVE "
				int lastMove =0; // If last move is made by 1st player it's 1 if 2nd player it's 2
				string command; //Holds the player's input
				int moveColumn; //Holds the choice of player's move
				int commandNo = -1; //0 for save, 1 for load, 2 for move -1 for unknown inputs
				string fileName; //Holds the name of the file name that user has given.
	
				properInput = 0;
				while(properInput == 0 && multiGame[objectNo-1].getWhosTurn() == 1){
					cout << "Player 1's Turn, Make your move." << endl << endl;
					cin.clear();
					getline(std::cin, command);
					if(command.length() == 0 || cin.eof() ){
						cerr << "End of file" << endl;
						exit(0);
					}
					commandNo = multiGame[objectNo-1].checkCommand(moveColumn, command);
					switch (commandNo) {
						case 0:
							//Getting fileName from Load Command
							if( command.length() > firstFive){
							for(int k=firstFive, i=0; k<command.length(); ++k, ++i)
								fileName[i] = command[k];
								multiGame[objectNo-1].saveToFile(fileName);
							}
							else
								cerr << "Unknown input. Couldn't find the file name" << endl;
							break;
						case 1:
							//Getting fileName from Load Command
							if( command.length() > firstFive){
								for(int k=firstFive,  i=0; k<command.length(); ++k, ++i)
									fileName[i] = command[k];
								multiGame[objectNo-1].loadFromFile(fileName);
							}
							else
								cerr << "Unknown input. Couldn't find the file name" << endl;
							break;
						case 2:
							if( command.length() == 1){
								properInput = 1;
								moveColumn = multiGame[objectNo-1].charToInt(command[0]);
								multiGame[objectNo-1].play(moveColumn);
								multiGame[objectNo-1].setWhosTurn(2);
								multiGame[objectNo-1].printBoard();
								lastMove = 1;
								if( multiGame[objectNo-1].checkWinner() == 1 ) //There's a winner
									multiGame[objectNo-1].setIsGameOver(1);
								else if( multiGame[objectNo-1].checkWinner() == 2) //Game is Draw
									multiGame[objectNo-1].setIsGameOver(2);
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
				if(multiGame[objectNo-1].getIsGameOver() == 0 && multiGame[objectNo-1].getWhosTurn() == 2){
					if(multiGame[objectNo-1].getIsAI() == 1){
						cout << "Comptuer's Turn." << endl << endl;
						multiGame[objectNo-1].play();
						multiGame[objectNo-1].printBoard();
						multiGame[objectNo-1].setWhosTurn(1);
						lastMove = 2;
						if( multiGame[objectNo-1].checkWinner() == 1 ) //There's a winner
							multiGame[objectNo-1].setIsGameOver(1);
						else if( multiGame[objectNo-1].checkWinner() == 2) //Game is Draw
							multiGame[objectNo-1].setIsGameOver(2);
					}
					else{
						properInput = 0;
						while( properInput == 0){
							cout << "Player 2's Turn, Make your move." << endl << endl;
							cin.clear();
							getline(std::cin, command);
							if(command.length() == 0 || cin.eof() ){
								cerr << "End of file" << endl;
								exit(0);
							}
							commandNo = multiGame[objectNo-1].checkCommand(moveColumn, command);
							switch (commandNo) {
								case 0:
									//Getting fileName from Load Command
									if( command.length() > firstFive){
									for(int k=firstFive, i=0; k<command.length(); ++k, ++i)
										fileName[i] = command[k];
									multiGame[objectNo-1].saveToFile(fileName);
									}
									else
										cerr << "Unknown input. Couldn't find the file name" << endl;
									break;
								case 1:
									//Getting fileName from Load Command
									if( command.length() > firstFive){
										for(int k=firstFive,  i=0; k<command.length(); ++k, ++i)
											fileName[i] = command[k];
										multiGame[objectNo-1].loadFromFile(fileName);
									}
									else
										cerr << "Unknown input. Couldn't find the file name" << endl;
									break;
								case 2:
									if( command.length() == 1){
										properInput = 1;
										moveColumn = multiGame[objectNo-1].charToInt(command[0]);
										multiGame[objectNo-1].play(moveColumn);
										multiGame[objectNo-1].setWhosTurn(1);
										multiGame[objectNo-1].printBoard();
										lastMove = 2;
										if( multiGame[objectNo-1].checkWinner() == 1 ) //There's a winner
											multiGame[objectNo-1].setIsGameOver(1);
										else if( multiGame[objectNo-1].checkWinner() == 2) //Game is Draw
											multiGame[objectNo-1].setIsGameOver(2);
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
				cout << "Current Living cell number: " << multiGame[objectNo-1].livingCellCount() << endl;
				if( multiGame[objectNo-1].checkWinner() == 1 )
					multiGame[objectNo-1].setIsGameOver(1);
				}
			
				if(multiGame[objectNo-1].getIsGameOver() == 1){
					if(multiGame[objectNo-1].getIsAI() == 1 && lastMove == 2)
						cout << "Computer won!!!" << endl;
					else
						cout << "Player " << lastMove << " won!!!" << endl << endl;
				}
				else if( multiGame[objectNo-1].getIsGameOver() == 2 )
					cout << "DRAW!!" << endl << endl;
	
				multiGame[objectNo-1].printBoard(); //Printing the final board						
			}
		}		
	}
		
	cout << "Thanks for playing!" << endl;
		
	return 0;
}
