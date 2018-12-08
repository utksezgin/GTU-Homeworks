#include "CPUProgram.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//Default Constructor
CPUProgram::CPUProgram()
{
    lineCount=0;
}

//Copy Constructor
CPUProgram::CPUProgram(CPUProgram &newProg)
{
    lineCount=0;
    this->lineArr=newProg.lineArr;
    this->lineCount=newProg.lineCount;
    this->option=newProg.option;
}

//Reads file from the given filename
void CPUProgram::ReadFile(const char* &fileName)
{
//Opening the file
    ifstream program;
    string line;
    program.open(fileName);

    if (program.is_open())
    {
        while( getline (program, line))
        {
            lineArr.push_back(line);
            lineCount++;
        }
    }
    else
    {
        cout << "Couldnt open the file";
    }
    program.close();
}

//Returns the size of program
int CPUProgram::sizeCounter(string &fileName)
{
    return lineArr.size();
}

// Returns the line of given number
string CPUProgram::getLine(int index)const
{
    if(index<0)
    {
        cout << "Index cannot be negative";
        exit(1);
    }
    return lineArr[index];
}

////////////////////////////////////
//      Operator Overloading      //
////////////////////////////////////

string CPUProgram::operator[](int index)
{
    if(index<0 || index==lineArr.size())
    {
        cout << "Invalid index" << endl;
        exit(1);
    }
    else
        return lineArr[index];

}
CPUProgram& CPUProgram::operator=(CPUProgram &myProg2)
{
    this->lineArr=myProg2.lineArr;
    this->lineCount=myProg2.lineCount;
    this->option=myProg2.option;
    return *this;
}

CPUProgram operator+( CPUProgram &myProgram, const string inst)
{
    CPUProgram newProg(myProgram);
    myProgram.setLine(inst);
    return newProg;
}

CPUProgram& CPUProgram::operator+=(const string inst)
{
    this->setLine(inst);
    return *this;
}

CPUProgram& CPUProgram::operator+(CPUProgram &myProg2)
{
    for(int i=0;i<myProg2.getLineCount();++i)
    {
        this->setLine(myProg2.getLine(i));
    }
    return *this;
}

// Comparison operators
bool CPUProgram::operator<(CPUProgram &myProg2)
{
    if(this->getLineCount() < myProg2.getLineCount())
        return true;
    else
        return false;
}

bool CPUProgram::operator<=(CPUProgram &myProg2)
{
    if(this->getLineCount() <= myProg2.getLineCount())
        return true;
    else
        return false;
}

bool CPUProgram::operator>(CPUProgram &myProg2)
{
    if(this->getLineCount() > myProg2.getLineCount())
        return true;
    else
        return false;
}

bool CPUProgram::operator>=(CPUProgram &myProg2)
{
    if(this->getLineCount() >= myProg2.getLineCount())
        return true;
    else
        return false;
}

bool CPUProgram::operator==(CPUProgram &myProg2)
{
    if(this->getLineCount() == myProg2.getLineCount())
        return true;
    else
        return false;
}

bool CPUProgram::operator!=(CPUProgram &myProg2)
{
    if(*this == myProg2)
        return false;
    else
        return true;
}

//Decrement Operators
CPUProgram& CPUProgram::operator--()
{
    this->deleteLastLine();
    return *this;
}

CPUProgram CPUProgram::operator--(int)
{
    CPUProgram tempProg(*this);
    --*this;
    return tempProg;
}

//Stream insertion operator

ostream& operator<<(ostream& myCout,const CPUProgram &myProg )
{
    for(int i=0; i<myProg.getLineCount();++i)
    {
        myCout << myProg.getLine(i) << endl;
    }
    return myCout;
}

CPUProgram CPUProgram::operator()(int index1, int index2)
{
    CPUProgram newProg;

    if(index1<0 || index2<0)
    {
        cout << "Invalid index" << endl;
        exit(1);
    }
    else
    {
        if(index1>index2)
        {
            for(int i=index2;i<=index1;++i)
            {
                newProg.setLine(this->getLine(i));
            }
        }
        else
        {
            for(int i=index1;i<=index2;++i)
            {
                newProg.setLine(this->getLine(i));
            }
        }
    }
    return newProg;
}

