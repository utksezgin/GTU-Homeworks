#include "Cell.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

Cell::Cell(){
	width = 0;
	height = 0;
	winnerCell =0;
	status = "Empty";
}

Cell::Cell(int w, int h){
	if(w>= 0 && w <26)
		width = w;
	else{
		cerr << "Cell column cannot be " << w << endl;
		exit(-1);
	}
	
	if(h>=0)
		height = h;
	winnerCell =0;
}

void Cell::setWidth(int w){
	if(w>= 0 && w <26)
		width = w;
	else{
		cerr << "Cell column cannot be " << w << endl;
		exit(-1);
	}
}
	
void Cell::setHeight(int w){
	if(w>=0)
		height = w;	
}

void Cell::setStatus(string x){
	if(x == "Empty" || x == "User1" || x == "User2" || x == "Computer")
		status = x;
	else{
		cerr << "Unknown status" << endl;
		exit(-1);
	}
}

