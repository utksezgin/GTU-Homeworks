#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "Cell.h"
#include <iostream>
#include <string>
#include <stdlib.h> //Exit
#include <fstream> //Read/Write files
#include <math.h>

using namespace std;


int myNameSpace::ConnectFourPlus::checkWinner(){
	const int OFFSET = 3;
	int isWinner = 2; //Set to 2 by default. 2 Stands for draw.
	int winnerCell =1;
	//Checking for Draw.
	for(int i=0; i<maxHeight; ++i){   //i stands for columns
		for(int j=0; j<maxWidth; ++j){ //j stands for rows
			if(gameBoard[i][j].getStatus() == "Empty"){ //If there's an empty cell, it's not draw
				isWinner = -1;
			}
		}
	}
	
	for(int i=0; i<maxHeight; ++i){   //i stands for columns
		for(int j=0; j<maxWidth; ++j){ //j stands for rows
			if(gameBoard[i][j].getStatus() != "Empty"){ //Checks if that cell is empty			
				if(j<maxWidth-OFFSET){ //Preventing overflow
					if(gameBoard[i][j].getStatus() == gameBoard[i][j+1].getStatus() ){       	//Checking rightwards       
						if(gameBoard[i][j].getStatus() == gameBoard[i][j+2].getStatus() ){		//horizontal
							if(gameBoard[i][j].getStatus() == gameBoard[i][j+3].getStatus() ){
								isWinner = 1;
								gameBoard[i][j].setWinnerCell(winnerCell);
								gameBoard[i][j+1].setWinnerCell(winnerCell);
								gameBoard[i][j+2].setWinnerCell(winnerCell);
								gameBoard[i][j+3].setWinnerCell(winnerCell);
							}
						}
					}
				}
				if(isWinner != 1){
					if(j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i][j-1].getStatus() ){       	//Checking leftwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i][j-2].getStatus() ){		//horizontal
								if(gameBoard[i][j].getStatus() == gameBoard[i][j-3].getStatus() ){
									isWinner = 1;
									gameBoard[i][j].setWinnerCell(winnerCell);
									gameBoard[i][j-1].setWinnerCell(winnerCell);
									gameBoard[i][j-2].setWinnerCell(winnerCell);
									gameBoard[i][j-3].setWinnerCell(winnerCell); 
								} 
							}
						}
					}
				}
				if(isWinner != 1){
					if(i<maxHeight-OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j].getStatus() ){       	//Checking downwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j].getStatus() ){		//vertical
								if(gameBoard[i][j].getStatus() == gameBoard[i+3][j].getStatus() ){
									isWinner = 1;
									gameBoard[i][j].setWinnerCell(winnerCell);
									gameBoard[i+1][j].setWinnerCell(winnerCell);
									gameBoard[i+2][j].setWinnerCell(winnerCell);
									gameBoard[i+3][j].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j].getStatus() ){       	//Checking upwards       
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j].getStatus() ){		//vertical
								if(gameBoard[i][j].getStatus() == gameBoard[i-3][j].getStatus() ){
									isWinner = 1;
									gameBoard[i][j].setWinnerCell(winnerCell);
									gameBoard[i-1][j].setWinnerCell(winnerCell);
									gameBoard[i-2][j].setWinnerCell(winnerCell);
									gameBoard[i-3][j].setWinnerCell(winnerCell);
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
