//
// SymTest.cpp 
//
// Author: Chris Anderson  
// (C) UCLA 2012 
//
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <stdexcept>
using namespace std;

#include <SymFun.h>


//
//######################################################################
//
// SymTest.cpp : A CAMsymbolicFunction Demonstration Program. 
//
// This sample demonstrates the declaration and initialization
// of a SCC:SymFun function instance. The program also demonstrates
// capturing a line of console input into a STL string instance.
//
// INPUT :
// ------
// User is prompted to specify a function f(x,y) of two variables
//
// Example :  Typing x*x + 2*y followed by an enter would input
// the function x squared plus 2*y. The syntax for function specification
// is that of the syntax for a C++ expression. There is an additional
// feature that ^ is used to denote exponentiation, e.g. 
// x^2 = x*x.
//
// User is prompted to specify the evaluation point
//
// OUTPUT :
// ------
//
// The value of the function at the evaluation point
//
//
//######################################################################
//
int main()
{
    std::string functionString;       // STL string to hold function specification

    SCC::SymFun F;                         // create CAMsymbolicFunction instance
    const char*V [] = {"x","y"};      // x,y  = independent variables
//
//  Obtain function input.
//  Repeat request until an acceptable function is specified
//  or enter is hit (the latter terminates the program)
//
//
    bool repeatFlag = true;
    int errorFlag   = 0;

    while(repeatFlag)
    {
    cout << "Enter f(x,y)  : ";
    getline(cin,functionString,'\n');  //     : stop reading at newline

    if(functionString.length()== 0)
    {
    cout << "XXX Execution Complete XXX " << endl;
    exit(0);
    }

//  Echo input

    cout << "Function Input : " << functionString.c_str( ) << endl << endl;
    
    // initialize SCC::SymFun

    try
	{
    errorFlag = F.initialize(V,2,functionString.c_str());

	if(errorFlag == 0) repeatFlag = false;}
    catch (const SCC::SymFunException& e)
	{
     cout << e.what() << endl;
	}

    }

    double x;  
    double y;

    cout <<  "Enter the evaluation point coordinates " << endl << endl ;
    cout <<  " x = ";
    cin  >> x;
    cout <<  " y = ";
    cin  >> y;
 
    // Evaluate the SCC::SymFun instance then print out result

    double val = F(x,y);

    cout << endl;
    cout << "The SCC::SymFun instance specification : " << functionString << endl;
    cout << "The value of the SCC::SymFun instance at (x,y) = ("
		 << x << ", "<< y << ") is : ";

    cout << val << endl << endl;
    cout << "XXX Execution Complete XXX " << endl;

    return 0;
}

