#ifndef CELL_H
#define CELL_H
#include <iostream> //delete this
#include <string>	//delete this
using namespace std;

class Cell{
	public:
		Cell(); //Default constructor Sets Column to A, row to 0 and status to empty.
		Cell(int col, int r); // Sets col to column, row to row and status to empty.
		inline int getWinnerCell() const { return winnerCell; };
		inline int getHeight() const { return height; };
		inline int getWidth() const { return width; };
		inline string getStatus() const { return status; };
		inline void setWinnerCell(int w) { winnerCell = w; };
		void setHeight(int h);
		void setWidth(int w);
		void setStatus(string x);
	private:
		int winnerCell; //1 if one of the 4 cells otherwise 0
		int width;	 //A,B,C,....,Z ** 0-26
		int height;	    //0,1,2,3...
		string status;  //Empty, User1, User2, Computer

};

#endif
