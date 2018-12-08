#include "ConnectFourAbstract.h"
#include "ConnectFourDiag.h"
#include "Cell.h"
#include <iostream>
#include <string>
#include <stdlib.h> //Exit
#include <fstream> //Read/Write files
#include <math.h>

using namespace std;


int myNameSpace::ConnectFourDiag::checkWinner(){
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
				if(isWinner !=1){
					if(i>OFFSET-1 && j<maxWidth - OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j+1].getStatus() ){       	//Top-Right      
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j+2].getStatus() ){		//Diagonal
								if(gameBoard[i][j].getStatus() == gameBoard[i-3][j+3].getStatus() ){
									isWinner = 1;
									gameBoard[i][j].setWinnerCell(winnerCell);
									gameBoard[i-1][j+1].setWinnerCell(winnerCell);
									gameBoard[i-2][j+2].setWinnerCell(winnerCell);
									gameBoard[i-3][j+3].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i>OFFSET-1 && j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i-1][j-1].getStatus() ){       	//Top-Left     
							if(gameBoard[i][j].getStatus() == gameBoard[i-2][j-2].getStatus() ){		//Diagonal
								if(gameBoard[i][j].getStatus() == gameBoard[i-3][j-3].getStatus() ){
									isWinner = 1;
									gameBoard[i][j].setWinnerCell(winnerCell);
									gameBoard[i-1][j-1].setWinnerCell(winnerCell);
									gameBoard[i-2][j-2].setWinnerCell(winnerCell);
									gameBoard[i-3][j-3].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i<maxHeight - OFFSET && j<maxWidth - OFFSET){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j+1].getStatus() ){       	//Bottom-Right      
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j+2].getStatus() ){		//Diagonal
								if(gameBoard[i][j].getStatus() == gameBoard[i+3][j+3].getStatus() ){
									isWinner = 1;
									gameBoard[i][j].setWinnerCell(winnerCell);
									gameBoard[i+1][j+1].setWinnerCell(winnerCell);
									gameBoard[i+2][j+2].setWinnerCell(winnerCell);
									gameBoard[i+3][j+3].setWinnerCell(winnerCell);
								}
							}
						}
					}
				}
				if(isWinner !=1){
					if(i<maxHeight - OFFSET && j>OFFSET-1){ //Preventing overflow
						if(gameBoard[i][j].getStatus() == gameBoard[i+1][j-1].getStatus() ){       	//Bottom-Left     
							if(gameBoard[i][j].getStatus() == gameBoard[i+2][j-2].getStatus() ){		//Diagonal
								if(gameBoard[i][j].getStatus() == gameBoard[i+3][j-3].getStatus() ){
									isWinner = 1;
									gameBoard[i][j].setWinnerCell(winnerCell);
									gameBoard[i+1][j-1].setWinnerCell(winnerCell);
									gameBoard[i+2][j-2].setWinnerCell(winnerCell);
									gameBoard[i+3][j-3].setWinnerCell(winnerCell);
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
