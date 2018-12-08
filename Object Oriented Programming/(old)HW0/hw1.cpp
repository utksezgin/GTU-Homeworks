#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

//Checks if the given input is register and returns 1 if it is and -1 for non-register inputs
//Also passes the index of the register by reference if its a register
int isValidRegister(string input, int &index);

//Returns 1 if the input string is numeric
int isStringNumber(string line);

//Converts string into integer
int stringToInt(string input);

//Returns how many components are there in a single line of instruction
int howManyComponents(string instruct, string reg1, string reg2);

//Puts the value of reg1 into reg2
void moveReg(int *regArr, int index1, int index2);

//Puts input into reg1
void moveConst(int *regArr, int index1, int input);

//adds value2 to value1 and returns value1
int addition(int value1, int value2);

//Substracts value2 from value1 and returns value1
int substraction(int value1, int value2);

//Jumps to given line directly
int jump(int newIndex);

//Jumps to the given line if the given input is 0
int jump(int reg, int currentIndex, int newIndex);

//Prints output1 to the screen
void prnt(int output1);

//Halts the program and prints registers, returns 1 for program to stop
int halt(int *regArr, int lineCount);

//Starts program and executes the instructions
int startProgram(string line, string &instruct, string &reg1, string &reg2, int lineCount, int *regArr);

//Seperates the instruction lines and makes assignments returns 1 if there is a syntax error
int getInstructions(string line, string &instruct, string &reg1, string &reg2);

//Lowercase to uppercase
void lowerToUpper(string &command);

//Prints the instructionLine
void printInstructionLine(int *regArr, int LineCount, char *option, string lineArr);



int main(int argc, char *argv[])
{
    int const MAX_LINE = 100;//Maximum lines on the instruction
    int const REG_COUNT = 5;//Number of registers    
    int lineCount=0;//Count of total lines on the program
    int componentCount=0;//Count of component of the instruction
	string tempCommand; //Temporary string for command
    string command[MAX_LINE];//String array for commands
    string input1[MAX_LINE];//String array for first input
    string input2[MAX_LINE];//String array for second input
    string lineArr[MAX_LINE];//String array for instruction lines
    int regArr[REG_COUNT];//Register array
    int regIndex1=0;//Array index number 1
    int regIndex2=0;//Array index number 2


	//Initialization of registers
    for(int i=0;i<REG_COUNT;i++)
    {
        regArr[i]=0;
    }


    //Opening the file
    ifstream program;
    program.open(argv[1]);

	//Assignment of the instruction lines from file to string array
    if (program.is_open())
    {
        while( getline (program,lineArr[lineCount]))
        {
            lineCount++;
        }
    }


    int i=0;
    int stop=0; //Gets the value of 1 if there is any syntax or any other errors
    if(argc!=3) 
    {
        cout << "Missing arguments";
    }
    else
    {
        while(stop!=1)
        {
            if(getInstructions(lineArr[i],command[i], input1[i],input2[i])==1 )
            {
                stop=1;
                cout << "Syntax error";
            }
            else
            {
				//Initializing and counting the components of instructions
                componentCount = howManyComponents(command[i], input1[i], input2[i]);
                lowerToUpper(command[i]);
				tempCommand=command[i];
                    if( command[i]=="MOV")
                    {
                        if( isValidRegister(input1[i], regIndex1)==1 )
                        {
                            if(isValidRegister(input2[i],regIndex2)==1 )
                            {
                                moveReg(regArr,regIndex1,regIndex2);
                            }
                        else if( isStringNumber(input2[i])==1 )
                        {
                            moveConst(regArr,regIndex1, stringToInt(input2[i]) );
                        }

                        }
                        else
                        {
                             cout << "Syntax Error";
                             stop=1;
                        }
                    }
                    else if(command[i]=="PRN")
                    {
                        if(isValidRegister(input1[i],regIndex1)==1)
                        {
                            prnt(regArr[regIndex1]);
                        }
                        else if(isStringNumber(input1[i])==1)
                            {
                                prnt(stringToInt(input1[i]));
                            }
                        else
                        {
                             cout << "Ssyntax Error";
                             stop=1;
                        }
                    }
                    else if(command[i]=="SUB")
                    {
                        if( isValidRegister(input1[i], regIndex1)==1 )
                        {
                            if(isValidRegister(input2[i],regIndex2)==1)
                            {
                                regArr[regIndex1]=substraction( regArr[regIndex1], regArr[regIndex2] );
                            }
                            else if(isStringNumber( input2[i] ) == 1 )
                            {
                                regArr[regIndex1] = substraction( regArr[regIndex1], stringToInt(input2[i]) );
                            }
                            else
                            {
                                 cout << "Syntax Error";
                                 stop=1;
                            }
                        }
                    }
                    else if(command[i]=="ADD")
                    {
                        if( isValidRegister(input1[i], regIndex1)==1 )
                        {
                            if(isValidRegister(input2[i],regIndex2)==1)
                            {
                                regArr[regIndex1]=addition( regArr[regIndex1], regArr[regIndex2] );
                            }
                            else if(isStringNumber( input2[i] ) == 1 )
                            {
                                regArr[regIndex1] = addition( regArr[regIndex1], stringToInt(input2[i]) );
                            }
                            else
                            {
                                 cout << "Syntax Error";
                                 stop=1;
                            }
                        }
                    }
                    else if(command[i]=="HLT")
                    {
                        stop=halt(regArr, lineCount);
                    }
                    else if(command[i]=="JMP")
                    {
                        if(componentCount==3)
                        {
                            if(isValidRegister(input1[i], regIndex1)==1)
                            {
                                i= jump(regArr[regIndex1], i, stringToInt(input2[i]));
                            }
                        }
                        else if(componentCount==2)
                        {
                            i= jump(stringToInt(input1[i]));
                        }
                        else
                        {
                             cout << "Syntax Error";
                             stop=1;
                        }
                    }
                    else
                    {
                        cout << "Syntax Error";
                        stop=1;
                    }

					if(stop!=1)
                    {
                            printInstructionLine(regArr, lineCount, argv[2], lineArr[i]);
                    }	
                    if(tempCommand!="JMP")
                        ++i;

            }
        }
    }



    return 0;
}



int getInstructions(string line, string &instruct, string &reg1, string &reg2)
{

    int err=0; //If err is 1 then there is a syntax error on the program
    int j=0;



        //Skips spaces and commas
        while(  (line[j]==' ' || line[j]==',') && line.size()>j )
        {
            if(line[j]==' ')
            {
                if(line[j]!=' ' && line[j]!=',' && line[j]!='r' && line[j]!='R')
                {
                    err=1;
                }
                j++;
            }

        }

        //Gets the instruction and assigns it into a seperate string
        instruct.clear();
        while(line[j]!=' ' && line[j]!=',' && line[j]!=';')
        {
            instruct+=line[j];
            ++j;
        }
        //Skips spaces and commas

        while(  (line[j]==' ' || line[j]==',') && line.size()>j )
        {
            if(line[j]!=' ' && line[j]!=',' && line[j]!='r' && line[j]!='R')
            {
                err=1;
            }
            j++;
        }

        // Gets the first input if there is one and assigns it into a seperate string
        reg1.clear();
         while(line[j]!=' ' && line[j]!=',' && line[j]!=';')
        {
            int k=0;
            reg1+=line[j];
            ++k;
            ++j;
        }


         //Skips spaces and commas
        while(  (line[j]==' ' || line[j]==',') && line.size()>j )
        {
            if(line[j]!=' ' && line[j]!=',' && line[j]!='r' && line[j]!='R')
            {
                err=1;
            }
            j++;
        }

        // Gets the second input if there is one and assigns it into a seperate string
        reg2.clear();
         while(line[j]!=' ' && line[j]!=',' && line[j]!=';')
        {
            reg2+=line[j];
            ++j;
        }

        //Checking for unusual character to see if syntax is correct.
        while( line[j]!=';' && line[j]!='\n' && line.size()>j)
        {
            if(line[j]!=' ' && line[j]!=',' && line[j]!='r' && line[j]!='R')
            {
                err=1;
            }
            j++;
        }

    return err;

}


void prnt(int output1)
{

    cout << output1 << endl;

}



int jump(int newIndex)
{
    return newIndex-1;
}


int jump(int reg, int currentIndex, int newIndex)
{
    if(reg==0)
    {
        return newIndex-1;
    }
    else
        return ++currentIndex;
}

int halt(int *regArr, int lineCount)
{
    for(int i=0;i<lineCount-1;++i)
    {
        cout << "R" << i+1 << "=" << regArr[i] <<" ";
    }

    cout << endl;

    return 1;
}


int addition(int value1, int value2)
{
    return (value1+=value2);
}


 int substraction(int value1, int value2)
 {
     return (value1-=value2);
 }


void moveReg(int *regArr, int index1, int index2)
{
    regArr[index2]=regArr[index1];
}


void moveConst(int *regArr, int index1, int input)
{
    regArr[index1]=input;
}


void lowerToUpper(string &command)
{
    for(int i=0;i<command.size(); ++i)
    {
        if(command[i]>'a' && command[i]<'z')
        {
            command[i]-=32;
        }
    }

}

int isStringNumber(string line)
{
    int isAllNumber = 0;

    for(int i=0;i<line.size();i++)
    {
        if( line[i]>='0' && line[i]<='9' )
        {
            isAllNumber = 1;
        }
        else
        {
            isAllNumber = 0;
            return isAllNumber;
        }
    }
    return isAllNumber;
}


int isValidRegister(string input, int &index)
{
    int isRegister=-1;

    if(input.size()>2) //Since there are 5 registers which means 2 characters in strings there cant be more than 2
    {
        return isRegister;
    }
    else if(input[0]!='R' && input[0]!='r')
    {
        return isRegister;
    }
    else
    {
        if(input[1]>'5')
        {
            return isRegister;
        }
        else
        {
            index=input[1]-'0'-1;
            isRegister=1;
            return isRegister;
        }
    }

}



int howManyComponents(string instruct, string reg1, string reg2)
{
    int const MAX_COMP=3;
    int compCount=0;
    int tempIndex=0;



    if(instruct.size()>0)
    {
        ++compCount;
    }

    if(reg1.size()>0 && (isValidRegister(reg1,tempIndex)==1 || isStringNumber(reg1)==1) )
    {
     ++compCount;
    }

    if(reg1.size()>0 && (isValidRegister(reg2,tempIndex)==1 || isStringNumber(reg2)==1) )
    {
     ++compCount;
    }


    return compCount;

}


int stringToInt(string input)
{
    int i=input.size();
    int number=0;

    while(i>0)
    {
        number += (input[i-1]-'0')*(pow(10,input.size()-i)) ;
        --i;
    }

    
    return number;

}

void printInstructionLine(int *regArr, int lineCount, char *option, string lineArr)
{
	
	
    if(*option=='1')
    {
        for(int i=0; i<lineArr.size() && lineArr[i]!=';' ; ++i)
        {
            cout << lineArr[i];
        }
        cout << " - ";

        for(int i=0;i<lineCount-1;++i)
    {
        cout << "R" << i+1 << "=" << regArr[i] <<" ";
    }

    cout << endl;

    }
}
