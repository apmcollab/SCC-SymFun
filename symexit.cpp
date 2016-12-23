//******************************************************************************
//                    SYMEXIT.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//            7/21/97
//
//
//********************************************************************************
//
#include "symexit.h"

#include <string>
#include <cstring>
#include <cstdlib> 
#include <iostream>
using namespace std;

#ifndef __BCPLUSPLUS__
void CAMsymExit()
{
	cerr << " Fatal Error : Program Stopped " << endl;
	exit(1);
};
void CAMsymExit(char* ErrorMessage)
{
	cerr << ErrorMessage << endl << endl << endl;
	cerr << " Fatal Error " << endl;
	exit(1);
};
#else
void CAMsymExit()
{
    cerr << endl << endl;
    cerr << "Hit return to Exit " << endl << endl;
    getchar();
	throw CAMsymException("Error In CAMsymbolicFunction Classes");
};
void CAMsymExit(char* ErrorMessage)
{
	 throw CAMsymException(ErrorMessage);
};
CAMsymException::CAMsymException()
{
	errorMessage = new char[1];
	errorMessage[0] = '\0';
}
CAMsymException::CAMsymException(char* Emessage)
{
    errorMessage = new char[strlen(Emessage) + 1];
    strcpy(errorMessage, Emessage);
}
CAMsymException::CAMsymException(const CAMsymException& C)
{
    errorMessage = new char[strlen(C.errorMessage) + 1];
    strcpy(errorMessage, C.errorMessage);
}
CAMsymException::~CAMsymException()
{
    delete [] errorMessage;
}
#endif
