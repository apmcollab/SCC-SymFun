//
//##################################################################
//  		        CAM REAL OPERATOR LIB
//        (FUNCTIONS USED BY CAM SYMBOLIC FUNCTION)
//
//##################################################################
//
// Version 1/22/2009                 Chris Anderson 9/10/96 (C) UCLA
//
//
#include "rOpLib.h"
#include "math.h"

#include <string>
#include <cstring>
#include <iostream>

using namespace std;
//
// Static Initialization
//
int   CAMrealOperatorLib::operatorCount = 26;

const char* CAMrealOperatorLib::Symbols[26]   =
{"+", "-", "+", "-", "*", "/","^","sin", "cos",
"tan","asin","acos","atan","atan2",
"sinh","cosh","tanh",
"ceil","exp","fabs","floor","fmod","log","log10","sqrt","pow"};


int   CAMrealOperatorLib::Priority[26]  =
{3,3,5,5,4,4,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int   CAMrealOperatorLib::ArgCount[26]  =
{1,1,2,2,2,2,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,2};

void* CAMrealOperatorLib::FunctionArray[26] =
{
(void*)CAMrealOperatorLib::Plus,
(void*)CAMrealOperatorLib::Minus,
(void*)CAMrealOperatorLib::Add,
(void*)CAMrealOperatorLib::Subtract,
(void*)CAMrealOperatorLib::Times,          // 5 //
(void*)CAMrealOperatorLib::Divide,
(void*)CAMrealOperatorLib::Exponentiate,
(void*)CAMrealOperatorLib::Sin,
(void*)CAMrealOperatorLib::Cos,
(void*)CAMrealOperatorLib::Tan,            // 10 //
(void*)CAMrealOperatorLib::Asin,
(void*)CAMrealOperatorLib::Acos,
(void*)CAMrealOperatorLib::Atan,
(void*)CAMrealOperatorLib::Atan2,           //14//
(void*)CAMrealOperatorLib::Sinh,
(void*)CAMrealOperatorLib::Cosh,
(void*)CAMrealOperatorLib::Tanh,
(void*)CAMrealOperatorLib::Ceil,
(void*)CAMrealOperatorLib::Exp,
(void*)CAMrealOperatorLib::Fabs,           // 20 //
(void*)CAMrealOperatorLib::Floor,
(void*)CAMrealOperatorLib::Fmod,
(void*)CAMrealOperatorLib::Log,
(void*)CAMrealOperatorLib::Log10,           // 24 //
(void*)CAMrealOperatorLib::Sqrt,            // 25 //
(void*)CAMrealOperatorLib::Pow
};


void CAMrealOperatorLib::Plus(double** argPtr)
{	*argPtr[1] =  +(*argPtr[0]);  }

void CAMrealOperatorLib::Minus(double** argPtr)
{	*argPtr[1] =  -(*argPtr[0]);  }


void CAMrealOperatorLib::Add(double** argPtr)
{ 	*argPtr[2] =  (*argPtr[0])+(*argPtr[1]); }

void CAMrealOperatorLib::Subtract(double** argPtr)
{ 	*argPtr[2] =  (*argPtr[0])-(*argPtr[1]); }

void CAMrealOperatorLib::Times(double** argPtr)
{	*argPtr[2] = (*argPtr[0])*(*argPtr[1]); }

void CAMrealOperatorLib::Divide(double** argPtr)
{	*argPtr[2] =  (*argPtr[0])/(*argPtr[1]); }

void CAMrealOperatorLib::Exponentiate(double** argPtr)
{	*argPtr[2] =  pow(*argPtr[0],*argPtr[1]); }

void CAMrealOperatorLib::Sin(double** argPtr)
{ 	*argPtr[1] = sin(*argPtr[0]); }

void CAMrealOperatorLib::Cos(double** argPtr)
{	*argPtr[1] = cos(*argPtr[0]); }

void CAMrealOperatorLib::Tan(double** argPtr)
{	*argPtr[1] = tan(*argPtr[0]); }

void CAMrealOperatorLib::Asin(double** argPtr)
{	*argPtr[1] = asin(*argPtr[0]); }

void CAMrealOperatorLib::Acos(double** argPtr)
{	*argPtr[1] = acos(*argPtr[0]); }

void CAMrealOperatorLib::Atan(double** argPtr)
{  *argPtr[1] = atan(*argPtr[0]); }

void CAMrealOperatorLib::Atan2(double** argPtr)
{ *argPtr[2] = atan2(*argPtr[0],*argPtr[1]);}

void CAMrealOperatorLib::Sinh(double** argPtr)
{	*argPtr[1] = sinh(*argPtr[0]); }

void CAMrealOperatorLib::Cosh(double** argPtr)
{	*argPtr[1] = cosh(*argPtr[0]); }

void CAMrealOperatorLib::Tanh(double** argPtr)
{	*argPtr[1] = tanh(*argPtr[0]); }

void CAMrealOperatorLib::Ceil(double** argPtr)
{	*argPtr[1] = ceil(*argPtr[0]); }

void CAMrealOperatorLib::Exp(double** argPtr)
{	*argPtr[1] = exp(*argPtr[0]); }

void CAMrealOperatorLib::Fabs(double** argPtr)
{	*argPtr[1] = fabs(*argPtr[0]); }

void CAMrealOperatorLib::Floor(double** argPtr)
{	*argPtr[1] = floor(*argPtr[0]); }

void CAMrealOperatorLib::Fmod(double** argPtr)
{ *argPtr[2] = fmod(*argPtr[0],*argPtr[1]);}

void CAMrealOperatorLib::Log(double** argPtr)
{	*argPtr[1] = log(*argPtr[0]); }

void CAMrealOperatorLib::Log10(double** argPtr)
{	*argPtr[1] = log10(*argPtr[0]); }

void CAMrealOperatorLib::Sqrt(double** argPtr)
{	*argPtr[1] = sqrt(*argPtr[0]); }

void CAMrealOperatorLib::Pow(double** argPtr)
{ *argPtr[2] = pow(*argPtr[0],*argPtr[1]);}


void CAMrealOperatorLib::evaluate(int, double** )
{
/*
	switch(i)
    {
    case 0 : Plus(argPtr);               break;
    case 1 : Minus(argPtr);              break;
    case 2 : Add(argPtr);                break;
    case 3 : Subtract(argPtr);           break;
    case 4 : Times(argPtr);              break;
    case 5 : Divide(argPtr);             break;
    case 6 : Exponentiate(argPtr);       break;
    case 7 : Sin(argPtr);                break;
    case 8 : Cos(argPtr);                break;
    case 9 : Atan2(argPtr);              break;
    }
*/
}


int CAMrealOperatorLib::getOperatorIndex(const char* Sym)
{
    int ireturn = -1;
    int i;
	for(i=0; i< operatorCount; i++)
    {
	if(strcmp(Sym,Symbols[i]) == 0) ireturn = i;
    }
    return ireturn;
}

int CAMrealOperatorLib::getUnaryOperatorIndex(const char* Sym)
{
    int ireturn = -1;
	if(strcmp(Sym,"+") == 0) ireturn = 0;
    if(strcmp(Sym,"-") == 0) ireturn = 1;
    return ireturn;
}

int CAMrealOperatorLib::getBinaryOperatorIndex(const char* Sym)
{
    int ireturn = -1;
	if(strcmp(Sym,"+") == 0) ireturn = 2;
    if(strcmp(Sym,"-") == 0) ireturn = 3;
    return ireturn;
}

int CAMrealOperatorLib::getOperatorPriority(int index)
{
 	return Priority[index];
}

int CAMrealOperatorLib::getOperatorArgCount(int index)
{
 	return ArgCount[index];
}

int CAMrealOperatorLib::getOperatorCount()
{
 	return operatorCount;
}

const char* CAMrealOperatorLib::getOperatorSymbol(int index)
{
 	return Symbols[index];
}
void** CAMrealOperatorLib::getFunctionArrayPtr()
{return FunctionArray;};

