//
//##################################################################
//  		        OPERATOR LIB (VIRTUAL BASE CLASS)
//            FOR CAM SYMBOLIC FUNCTION MATHEMATICAL OPERATORS
//##################################################################
//
//	                                 Chris Anderson 9/10/96 (C) UCLA
//
#ifndef  __OPERATOR_LIB__
#define  __OPERATOR_LIB__
#include "symfunimpexp.h"

class __IMPEXP__ CAMoperatorLib
{

public :

    virtual int  getOperatorIndex(const char*){return 0;};
    virtual int  getUnaryOperatorIndex(const char*){return 0;};
    virtual int  getBinaryOperatorIndex(const char*){return 0;};

    virtual int   getOperatorPriority(int index){return 0;};
    virtual const char* getOperatorSymbol(int index){return 0;};
    virtual int   getOperatorCount(){return 0;};
    virtual int   getOperatorArgCount(int index){return 0;};
};
#endif

