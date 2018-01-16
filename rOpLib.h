//
// rOpLib.h 
//
// Author: Chris Anderson  
// (C) UCLA 2012 
//
#ifndef  __REAL_OPERATOR_LIB__
#define  __REAL_OPERATOR_LIB__
#include "OpLib.h"

class  CAMrealOperatorLib : public CAMoperatorLib
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
#endif

