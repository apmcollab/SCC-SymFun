//
//##################################################################
//  		        CAM REAL OPERATOR LIB
//        (FUNCTIONS USED BY SYMFUN SYMBOLIC FUNCTION)
//
//##################################################################
//
// Chris Anderson 9/10/96 (C) UCLA
//
// Version 1/22/2009
//
/*
#############################################################################
#
# Copyright 1996-2019 Chris Anderson
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# For a copy of the GNU General Public License see
# <http://www.gnu.org/licenses/>.
#
#############################################################################
*/

#include <cmath>
#include <string>
#include <cstring>
#include <iostream>

#include "RealOperatorLib.h"

//
// Static Initialization
//
int   SCC::RealOperatorLib::operatorCount = 26;

const char* SCC::RealOperatorLib::Symbols[26]   =
{"+", "-", "+", "-", "*", "/","^","sin", "cos",
"tan","asin","acos","atan","atan2",
"sinh","cosh","tanh",
"ceil","exp","fabs","floor","fmod","log","log10","sqrt","pow"};


int  SCC::RealOperatorLib::Priority[26]  =
{3,3,5,5,4,4,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int   SCC::RealOperatorLib::ArgCount[26]  =
{1,1,2,2,2,2,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,2};

void* SCC::RealOperatorLib::FunctionArray[26] =
{
(void*)SCC::RealOperatorLib::Plus,
(void*)SCC::RealOperatorLib::Minus,
(void*)SCC::RealOperatorLib::Add,
(void*)SCC::RealOperatorLib::Subtract,
(void*)SCC::RealOperatorLib::Times,          // 5 //
(void*)SCC::RealOperatorLib::Divide,
(void*)SCC::RealOperatorLib::Exponentiate,
(void*)SCC::RealOperatorLib::Sin,
(void*)SCC::RealOperatorLib::Cos,
(void*)SCC::RealOperatorLib::Tan,            // 10 //
(void*)SCC::RealOperatorLib::Asin,
(void*)SCC::RealOperatorLib::Acos,
(void*)SCC::RealOperatorLib::Atan,
(void*)SCC::RealOperatorLib::Atan2,           //14//
(void*)SCC::RealOperatorLib::Sinh,
(void*)SCC::RealOperatorLib::Cosh,
(void*)SCC::RealOperatorLib::Tanh,
(void*)SCC::RealOperatorLib::Ceil,
(void*)SCC::RealOperatorLib::Exp,
(void*)SCC::RealOperatorLib::Fabs,           // 20 //
(void*)SCC::RealOperatorLib::Floor,
(void*)SCC::RealOperatorLib::Fmod,
(void*)SCC::RealOperatorLib::Log,
(void*)SCC::RealOperatorLib::Log10,           // 24 //
(void*)SCC::RealOperatorLib::Sqrt,            // 25 //
(void*)SCC::RealOperatorLib::Pow
};


void SCC::RealOperatorLib::Plus(double** argPtr)
{	*argPtr[1] =  +(*argPtr[0]);  }

void SCC::RealOperatorLib::Minus(double** argPtr)
{	*argPtr[1] =  -(*argPtr[0]);  }


void SCC::RealOperatorLib::Add(double** argPtr)
{ 	*argPtr[2] =  (*argPtr[0])+(*argPtr[1]); }

void SCC::RealOperatorLib::Subtract(double** argPtr)
{ 	*argPtr[2] =  (*argPtr[0])-(*argPtr[1]); }

void SCC::RealOperatorLib::Times(double** argPtr)
{	*argPtr[2] = (*argPtr[0])*(*argPtr[1]); }

void SCC::RealOperatorLib::Divide(double** argPtr)
{	*argPtr[2] =  (*argPtr[0])/(*argPtr[1]); }

void SCC::RealOperatorLib::Exponentiate(double** argPtr)
{	*argPtr[2] =  std::pow(*argPtr[0],*argPtr[1]); }

void SCC::RealOperatorLib::Sin(double** argPtr)
{ 	*argPtr[1] = std::sin(*argPtr[0]); }

void SCC::RealOperatorLib::Cos(double** argPtr)
{	*argPtr[1] = std::cos(*argPtr[0]); }

void SCC::RealOperatorLib::Tan(double** argPtr)
{	*argPtr[1] = std::tan(*argPtr[0]); }

void SCC::RealOperatorLib::Asin(double** argPtr)
{	*argPtr[1] = std::asin(*argPtr[0]); }

void SCC::RealOperatorLib::Acos(double** argPtr)
{	*argPtr[1] = std::acos(*argPtr[0]); }

void SCC::RealOperatorLib::Atan(double** argPtr)
{  *argPtr[1] = std::atan(*argPtr[0]); }

void SCC::RealOperatorLib::Atan2(double** argPtr)
{ *argPtr[2] = std::atan2(*argPtr[0],*argPtr[1]);}

void SCC::RealOperatorLib::Sinh(double** argPtr)
{	*argPtr[1] = std::sinh(*argPtr[0]); }

void SCC::RealOperatorLib::Cosh(double** argPtr)
{	*argPtr[1] = std::cosh(*argPtr[0]); }

void SCC::RealOperatorLib::Tanh(double** argPtr)
{	*argPtr[1] = std::tanh(*argPtr[0]); }

void SCC::RealOperatorLib::Ceil(double** argPtr)
{	*argPtr[1] = std::ceil(*argPtr[0]); }

void SCC::RealOperatorLib::Exp(double** argPtr)
{	*argPtr[1] = std::exp(*argPtr[0]); }

void SCC::RealOperatorLib::Fabs(double** argPtr)
{	*argPtr[1] = std::fabs(*argPtr[0]); }

void SCC::RealOperatorLib::Floor(double** argPtr)
{	*argPtr[1] = std::floor(*argPtr[0]); }

void SCC::RealOperatorLib::Fmod(double** argPtr)
{ *argPtr[2] = std::fmod(*argPtr[0],*argPtr[1]);}

void SCC::RealOperatorLib::Log(double** argPtr)
{	*argPtr[1] = std::log(*argPtr[0]); }

void SCC::RealOperatorLib::Log10(double** argPtr)
{	*argPtr[1] = std::log10(*argPtr[0]); }

void SCC::RealOperatorLib::Sqrt(double** argPtr)
{	*argPtr[1] = std::sqrt(*argPtr[0]); }

void SCC::RealOperatorLib::Pow(double** argPtr)
{ *argPtr[2] = std::pow(*argPtr[0],*argPtr[1]);}


void SCC::RealOperatorLib::evaluate(int, double** )
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


int SCC::RealOperatorLib::getOperatorIndex(const char* Sym)
{
    int ireturn = -1;
    int i;
	for(i=0; i< operatorCount; i++)
    {
	if(strcmp(Sym,Symbols[i]) == 0) ireturn = i;
    }
    return ireturn;
}

int SCC::RealOperatorLib::getUnaryOperatorIndex(const char* Sym)
{
    int ireturn = -1;
	if(strcmp(Sym,"+") == 0) ireturn = 0;
    if(strcmp(Sym,"-") == 0) ireturn = 1;
    return ireturn;
}

int SCC::RealOperatorLib::getBinaryOperatorIndex(const char* Sym)
{
    int ireturn = -1;
	if(strcmp(Sym,"+") == 0) ireturn = 2;
    if(strcmp(Sym,"-") == 0) ireturn = 3;
    return ireturn;
}

int SCC::RealOperatorLib::getOperatorPriority(int index)
{
 	return Priority[index];
}

int SCC::RealOperatorLib::getOperatorArgCount(int index)
{
 	return ArgCount[index];
}

int SCC::RealOperatorLib::getOperatorCount()
{
 	return operatorCount;
}

const char* SCC::RealOperatorLib::getOperatorSymbol(int index)
{
 	return Symbols[index];
}
void** SCC::RealOperatorLib::getFunctionArrayPtr()
{return FunctionArray;};

