//******************************************************************************
//                    SYMEXIT.H
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
#ifndef __CAMSYMEXIT__
#define __CAMSYMEXIT__


void  CAMsymExit();
void  CAMsymExit(char* ErrorMessage);

#ifdef __BCPLUSPLUS__

class __IMPEXP__ CAMsymException
{
	public :

	CAMsymException();
	CAMsymException(const CAMsymException& C);
	CAMsymException(char* msg);
    ~CAMsymException();
    
	char* getMessage() const {return errorMessage;};

	private :

	char* errorMessage;
};
#endif
#endif



