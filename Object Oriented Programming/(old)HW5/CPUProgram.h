#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class CPUProgram
{
    public:

        CPUProgram();
        CPUProgram(const char* &fileName){ReadFile(fileName); lineCount=0;};
        CPUProgram(int argvOpt){lineCount=0; option=argvOpt; lineCount=0;};
        CPUProgram(CPUProgram &newProg);
        CPUProgram(string line){lineArr.push_back(line);};

        void setLineCount(int instCount){lineCount=instCount;};
        void setOption(int optn){option=optn;};
        void setLine(string line){lineArr.push_back(line);};
        void ReadFile(const char* &fileName); //Reads instructions from the given file name
        void deleteLastLine(){lineArr.pop_back();}; //Deletes the last line in the program
        void changeLine(string newLine, int index){lineArr[index]=newLine;}; //Changes the given line with new line
        string getLine(int index)const;
        int getLineCount()const{return lineArr.size();};
        int getOption(){return option;};

        int sizeCounter(string &fileName);
        int size(){return lineArr.size();};
        vector <string> getLineArr() { return lineArr; };

        //Operator overloading

        friend CPUProgram operator+(CPUProgram &myProgram, const string inst);
        friend ostream& operator<<(ostream& myCout,const CPUProgram &myProg );


        CPUProgram& operator+=(const string inst);
        CPUProgram& operator+(CPUProgram &myProg2);
        CPUProgram& operator--();
        CPUProgram operator--(int);
        CPUProgram operator()(int index1, int index2);
        CPUProgram& operator=(CPUProgram &myProg2);
        string operator[](int index);

        bool operator<(CPUProgram &myProg2);
        bool operator<=(CPUProgram &myProg2);
        bool operator>(CPUProgram &myProg2);
        bool operator>=(CPUProgram &myProg2);
        bool operator==(CPUProgram &myProg2);
        bool operator!=(CPUProgram &myProg2);


    private:
        vector <string> lineArr;
        int lineCount;
        int option;
};

//Global Operator overloading
CPUProgram operator+(CPUProgram &myProgram, const string inst);

ostream& operator<<(ostream& myCout,const CPUProgram &myProg );

#endif // CPUPROGRAM_H
