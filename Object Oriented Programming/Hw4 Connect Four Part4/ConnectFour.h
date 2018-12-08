#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include <iostream>
#include <string>	
#include <vector>
#include "Cell.h"
using namespace std;


class ConnectFour{
	public:
		ConnectFour(); //Creates a 5x5 board game
		ConnectFour(int w); //Creates a 5xWidth board game **Width cannot be less than 4 and greater than 26
		ConnectFour(int h, int w); //Creates a HeightxWidth board game **Height and width cannot be less than 4 Width cannot be greater than 26
		ConnectFour(const ConnectFour& cF);//Copy Constructor
		ConnectFour(string fileName);//Constructor that reads from the given filename
		inline int getMaxWidth() const { return maxWidth; }; //Returns maxWidth
		inline int getMaxHeight() const { return maxHeight; }; //Returns maxHeight
		int getCellWidth(int height, int width) const;  //returns cell row
		int getCellHeight(int height, int width) const;  //Returns Cell column
		string getCellStatus(int height, int width) const; //Returns cell status
		inline int getIsAI() const { return isAI; };	//Returns iSAI member
		inline int getIsGameOver() const { return isGameOver; }; //Returns isGameOver member
		inline int getObjectNumber() const { return objectNumber; }; //Returns Object's number
		inline int getWhosTurn() const { return whosTurn; }; //Returns whosTurn member
		inline void setIsAI(int ai) { isAI = ai; };	//Setter for isAI
		inline void setWhosTurn(int turn) { whosTurn = turn; };	//Setter for whosTurn
		inline void setIsGameOver(int isOver) { isGameOver = isOver; }; //Setter for isGameOver	
		void resizeBoard(int newHeight, int newWidth); //Resizes the board	
		int charToInt(char c); //Converts a char to an integer
		int stringToInt(string str); //Converts a string to an integer
		void loadFromFile(string loadFile); //Loads from given file name -- Example: LOAD fileName.txt
		void saveToFile(string saveFile);  //Saves to given file name   --  Example: SAVE fileName.txt
		void readBoard(string fileName); //Reads a board from a file
		void printBoard();		//Prints current board						
		int checkWinner(); //Checks for winner/draw 1:Winner 2:Draw
		int checkCommand(int column, string input); //Checks user input for move, save or load.
		inline static int livingCellCount() { return livingCells; }; //Returns total living cells
		inline static int totalOjbects() { return objectCount; }; //Returns total object count
		void playGame(); //Gets necessary inputs from the player and plays the whole game.
		void play();	//Plays 1 turn for computer
		void play(int move); //Plays 1 turn for player
		
		ConnectFour& operator=(const ConnectFour& cF);
		bool operator==(const ConnectFour& c) const;
		bool operator!=(const ConnectFour& c) const;
		
		~ConnectFour();
	
	private:
		
		void makeMove(string player, int w); //Checks if the move is legal and makes the move.
		int checkIllegalMove(int w); //Checks if the move is illegal
		
		static int livingCells; //Holds total living cell count
		static int objectCount; //Hold total object count
		int isGameOver; //0:Game not over 1: Game over -> 2:Draw
		int objectNumber; //Holds the objects number
		int whosTurn; //Holds the information of who's turn to play 1 or 2
		int isAI;	//Holds if player's chosen to play against AI or Player
		int maxWidth; //4 Min - 26 Max   //Can be changed via constant integers
		int maxHeight; //4 Min - 50 Max //i.e MIN_HEIGHT, MAX_WIDTH etc.
		Cell ** gameBoard; //Holds information of cells on the board in Cell class objects
};

#endif

