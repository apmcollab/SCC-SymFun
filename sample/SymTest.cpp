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
using namespace std;

#include "symfun.h"
//
//######################################################################
//
// SymTest.cpp : A CAMsymbolicFunction Demonstration Program. 
//
// This sample demonstrates the declaration and initialization
// of a CAMsymbolic function instance. The program also demonstrates 
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
// Math 157                                                     1/16/09
//######################################################################
//
int main()
{
    std::string functionString;       // STL string to hold function specification
//
//  Obtain Function Input 
//
    cout << "Enter f(x,y)   : ";

    getline(cin,functionString,'\n');  //     : stop reading at newline  
//
//  Echo input
//
    cout << endl;
    cout << "Function Input : " << functionString.c_str( ) << endl << endl;
//
    CAMsymbolicFunction F;     // create CAMsymbolicFunction instance
    
    const char*V [] = {"x","y"};     // x,y  = independent variables
    
    // initialize CAMsymbolicFunction 

    int errorFlag   = F.initialize(V,2,functionString.c_str());  
    
    if(errorFlag != 0) // interrogate
    {                                                
     cout << "Error in Function Initialization " << endl;
     exit(1);
    }

    double x;  
    double y;

    cout <<  "Enter the evaluation point coordinates " << endl << endl ;
    cout <<  " x = ";
    cin  >> x;
    cout <<  " y = ";
    cin  >> y;
 
    // Evaluate the CAMsymbolicFunction instance then print out result

    double val = F(x,y);

    cout << endl;
    cout << "The CAMsymbolicFunction instance specification : " << functionString << endl;
    cout << "The value of the CAMsymbolicFunction instance at (x,y) = ("
		 << x << ", "<< y << ") is : ";

    cout << val << endl << endl;
    return 0;
}

