#include "Cell.h"
#include "ConnectFour.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

Cell::Cell(){
	width = 0;
	height = 0;
	winnerCell =0;
	isPlayable = 1;
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
	isPlayable = 1;
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


bool Cell::operator==(const Cell& c) const{
	if(this->width == c.width && this->height == c.height && this->status == c.status && this->isPlayable == c.isPlayable)
		return true;
	else
		return false;
}

bool Cell::operator!=(const Cell& c) const{
	return !(*this == c);	
}

Cell& Cell::operator++(){
	if(this->status == "Empty")
		this->status = "User1";
	else if(this->status == "User1")
		this->status = "User2";
	else if(this->status == "User2")
		this->status = "Computer";
	else if(this->status =="Computer")
		this->status = "Empty";
	
	return *this;
}

Cell Cell::operator++(int ignoreMe){
	Cell temp(*this);
	
	if(this->status == "Empty")
		this->status = "User1";
	else if(this->status == "User1")
		this->status = "User2";
	else if(this->status == "User2")
		this->status = "Computer";
	else if(this->status =="Computer")
		this->status = "Empty";
	
	return temp;
}
ostream& operator << (ostream& oput, const Cell& c){
	oput << "Width: " << c. width << "Height: " << c. height << "Status: " << c.status << endl;
}

istream& operator >> (istream& iput, Cell& c){
	cout << "Please enter Width ";
	iput >> c.width;
	if(c.width < 0){
		cerr << "Width cannot be less than 0" << endl;
		exit(-2);
	}
	
	cout << "Please enter Height ";
	iput >> c.height;
	if(c.height < 0){
		cerr << "Height cannot be less than 0" << endl;
		exit(-2);
	}
	iput.clear();
	cout << "Please enter Status (Empty, User1, User2, Computer) ";
	cin >> c.status;
	if(c.status != "Empty" && c.status != "User1" && c.status != "User2" && c.status != "Computer"){
		cerr << "Unknown input" << endl;
		exit(-2);
	}
	
}
