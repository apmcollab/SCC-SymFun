//
// rOpLib.h 
//
// Author: Chris Anderson  
// (C) UCLA 2012 
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
#include "OperatorLib.h"

#ifndef  __REAL_OPERATOR_LIB__
#define  __REAL_OPERATOR_LIB__

namespace SCC
{
class  RealOperatorLib : public SCC::OperatorLib
{

public :

    static void evaluate(int i, double** argPtr);

    int getOperatorIndex(const char*);
    int getUnaryOperatorIndex(const char*);
    int getBinaryOperatorIndex(const char*);

    int   getOperatorPriority(int index);
    const char* getOperatorSymbol(int index);
    int   getOperatorCount();
    int   getOperatorArgCount(int index);

    static void** getFunctionArrayPtr();

public :

//
//  Unary Operators
//
	static void Plus(double**);                    // +x //
    static void Minus(double**);                   // -x //


// Binary Operators

    static void Add(double**);                     // x + y //
    static void Subtract(double**);                // x - y //

    static void Times(double **);                  // x * y //
    static void Divide(double **);                 // x / y //
    static void Exponentiate(double **);           // x ^ y //
//
// Operators
//
    static void Sin(double**);
    static void Cos(double**);
    static void Tan(double**);
    static void Asin(double**);
    static void Acos(double**);
    static void Atan(double**);
	static void Atan2(double**);
    static void Sinh(double**);
    static void Cosh(double**);
    static void Tanh(double**);
    static void Ceil(double**);
    static void Exp(double**);
    static void Fabs(double**);
    static void Floor(double**);
    static void Fmod(double**);
    static void Log(double**);
    static void Log10(double**);
    static void Sqrt(double**);
    static void Pow(double**);
//
//  Symbol Table
//
	static int operatorCount;
	static const char* Symbols[];
    static int   Priority[];
    static int   ArgCount[];
    static void* FunctionArray[];
};
}
#endif

