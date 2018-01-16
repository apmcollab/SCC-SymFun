
//
//##################################################################
//                CAM SYMBOLIC FUNCTION
//##################################################################
//
//                                     Chris Anderson 7/21/97 (C) UCLA
/*! 
    \class SymFun
    \brief An instance of class SymFun implements a
    double valued function (of an arbitrary number of double arguments) 
    as specified by an initialization character string (i.e. symbolic initialization). 
    
    The syntax for the initialization string is that of general C++ expressions. 
    The initialization string can contain references to C++ math functions 
    (those in math.h) as well as symbolic constants. The ^ character can be used
    to specify exponentiation, e.g. x^2 = x*x.
    
    The () operator is overloaded so the standard functional 
    evaluation syntax, e.g. f(x), is used to evaluate the CAMsymbolicFuntion instance.
    
    Sample Usage:
\code
int Vcount = 2;                   // number of independent variables
char*V []  = {"x","y"};           // x,y  = independent variable names
char*S     = "x^2 + 2*y";         // specify a function 
     
SymFun F(V,Vcount,S); // initialize instance
    
cout << F(2.0,3.0) << endl;        // evaluate and output result at (x,y) = (2.0,3.0) 
\endcode

    @author Chris Anderson
    @date 7/21/97
    @version 01/22/09
    
*/
#ifdef _MSC_VER                   // Add so Visual-Studio doesn't
#define _CRT_SECURE_NO_DEPRECATE   // complain about use of strcpy.
#endif 

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "SymFun.h"
#include "symexit.h"
#include "exptrans.h"
#include "rOpLib.h"
//
//##################################################################
//                      CONSTRUCTORS
//##################################################################
//
/**
  Creates a "null" SymFun. The SymFun is initialized
  with the initialize member functions.
*/
SymFun::SymFun()
{
    constructorString = 0;

    variableNames     = 0;
    variableCount     = 0;

    constantNames     = 0;
    constantCount     = 0;
    constantValues    = 0;

    symbolCount       = 0;
    sNames            = 0;

    evaluationData     = 0;
    evaluationDataSize = 0;

    executionArray     = 0;
    executionArraySize = 0;

    LibFunctions       = 0;
}
/**
  Copy constructor.
*/
SymFun::SymFun(const SymFun& F)
{
//
//  Null initializers
//
    constructorString = 0;

     variableNames     = 0;
    variableCount     = 0;

    constantNames     = 0;
    constantCount     = 0;
    constantValues    = 0;

    symbolCount       = 0;
    sNames            = 0;

    evaluationData     = 0;
    evaluationDataSize = 0;

    executionArray     = 0;
    executionArraySize = 0;

//
//  Allocate Storage and Initalize
//
    int i;

    if(F.constructorString != 0)
    {
    constructorString = new char[strlen(F.constructorString) + 1];
    strcpy(constructorString,F.constructorString);
    }

    if(F.variableCount != 0)
    {
    variableNames  = new char*[F.variableCount];
    variableCount  = F.variableCount;

    for(i = 0; i < F.variableCount; i++)
    {
    variableNames[i] = new char[strlen(F.variableNames[i]) + 1];
    strcpy(variableNames[i],F.variableNames[i]);
    }
    }

    if(F.constantCount != 0)
    {
    constantNames  = new char*[F.constantCount];
    constantCount  = F.constantCount;
    constantValues = new double[F.constantCount];

    for(i = 0; i < F.constantCount; i++)
    {
    constantNames[i] = new char[strlen(F.constantNames[i]) + 1];
    strcpy(constantNames[i],F.constantNames[i]);
    constantValues[i] = F.constantValues[i];
    }
    }

    evaluationDataSize = F.evaluationDataSize;

    if(F.evaluationData != 0)
    {
    evaluationData     = new double[evaluationDataSize];
    for(i=0; i< evaluationDataSize; i++)
    {
    evaluationData[i] = F.evaluationData[i];
    }}

    executionArraySize = F.executionArraySize;
    
    if(F.executionArray != 0)
    {
    executionArray     = new long[executionArraySize];
    for(i=0; i< executionArraySize; i++)
    {
    executionArray[i] = F.executionArray[i];
    }}

    symbolCount = F.symbolCount;
    sNames      = new char*[symbolCount];
    for(i=0; i< symbolCount; i++)
    {
    sNames[i] = new char[strlen(F.sNames[i])+1];
    strcpy(sNames[i],F.sNames[i]);
    }

    LibFunctions       = CAMrealOperatorLib::getFunctionArrayPtr();
}
/**
Creates a SymFun in one variable, x, where the function is
specified by the null terminated string S. If the construction process 
fails, program execution stops and an error message is output.

@arg S: Null terminated character string in the variable x that 
specifies the function.
*/
SymFun::SymFun(char const* S)
{
    const char* V []      = {"x"};
    int Vcount            = 1;
    const char** C        = 0;
    int Ccount            = 0;
    double* Cvalues       = 0;

    create(V,Vcount,C,Ccount, Cvalues, S);
}
/**
Creates a SymFun of Vcount variables from the initialization
string S. S is a null terminated character string. If the construction process 
fails, program execution stops and an error message is output.

@arg V      : Array of null terminated strings specifying independent variable names
@arg Vcount : The number of independent variables
@arg S      : Null terminated character string specifying the function



Sample specification and use of a function of two variables x and y: 

\code
int Vcount = 2;                   // number of independent variables
char*V []  = {"x","y"};           // x,y  = independent variable names
char*S     = "x^2 + 2*y";         // specify a function 
     
SymFun F(V,Vcount,S); // initialize instance
    
cout << F(2.0,3.0) << endl;        // evaluate and output result at (x,y) = (2.0,3.0) 
\endcode
*/
SymFun::SymFun(const char** V, int Vcount, const char* S)
{

    const char** C        = 0;
    int Ccount            = 0;
    double* Cvalues       = 0;
    create(V,Vcount,C,Ccount, Cvalues, S);
}

/**
Creates a SymFun of Vcount variables and
Ccount symbolic constants from the initialization string S. 
If the construction process fails, program execution stops and an 
error message is output.
  
@arg V      : Array of null terminated strings specifying independent variable names
@arg Vcount : The number of independent variables
@arg S      : Null terminated character string specifying the function
@arg V      : Array of null terminated strings specifying symbolic constant names
@arg Ccount : The number of symbolic constants 
@arg Cvalues: The values of the symbolic constants
@arg S      : Null terminated character string specifying the function

Sample:
\code
//
//  Create a SymFun that implements a*x^2 + b*x + c;
//  a, b, c being symbolic constants.
//
    int Vcount       = 1;                        // number of independent variables
    char*V []        = {"x"};                    // specify variable name
    int Ccount       = 3;                        // number of symbolic constants
    char*C []        = {"a","b","c"};            // specify constant names
    double Cvalues[] = {1.0, 2.0, 1.0};          // initial values of a,b,c
    char* S = "a*x^2 + b*x + c";                 // initialization string

    SymFun f(V,Vcount,C,Ccount,Cvalues, S);

    cout << f << endl << endl;                    // print out function

    cout << "The value of the function at x = 1.0 is " 
         << f(1.0) << endl << endl;

    f.setConstantValue("a",2.0);                  // reset the symbolic constant
                                                  // a to have the value 2.0
    cout << f << endl << endl;                    // print out function

    cout << "The value of the function at x = 1.0 is  " 
         << f(1.0) << endl;
\endcode
*/

SymFun::SymFun(const char** V, int Vcount, const char** C,
int Ccount, double const* Cvalues, char const* S)
{
    create(V,Vcount,C,Ccount, Cvalues, S);
}

int SymFun::create(const char** V, int Vcount, const char** C,
int Ccount, double const* Cvalues, char const* S)
{
//
//  Allocate Storage and Initalize
//
    constructorString = new char[strlen(S) + 1];
    strcpy(constructorString,S);

    variableNames  = new char*[Vcount];
    variableCount  = Vcount;

    int i;
    for(i = 0; i < Vcount; i++)
    {
    variableNames[i] = new char[strlen(V[i]) + 1];
    strcpy(variableNames[i],V[i]);
    }

    constantNames  = new char*[Ccount];
    constantCount  = Ccount;
    constantValues = new double[Ccount];

    for(i = 0; i < Ccount; i++)
    {
    constantNames[i] = new char[strlen(C[i]) + 1];
    strcpy(constantNames[i],C[i]);
    constantValues[i] = Cvalues[i];
    }

    CAMrealOperatorLib L;
      expressionTransform T;
    int expReturn;

    expReturn =  T.initialize(variableNames, variableCount, constantNames,
                 constantCount,constructorString,&L);
    if(expReturn != 0) {destroy(); return 1;}

    evaluationDataSize = T.getEvaluationDataSize();
    evaluationData     = new double[evaluationDataSize];

    executionArraySize = T.getExecutionArraySize();
    executionArray     = new long[executionArraySize];

    initializeEvaluationData(T);
    initializeExecutionArray(T);
//
//  Save symbols
//
    symbolCount    = T.getSymbolCount();
    char** TsNames = T.getSymbolNamesPtr();
    sNames      = new char*[symbolCount];
    for(i=0; i< symbolCount; i++)
    {
    sNames[i] = new char[strlen(TsNames[i])+1];
    strcpy(sNames[i],TsNames[i]);
    }

    LibFunctions       = CAMrealOperatorLib::getFunctionArrayPtr();
    return 0;
}
//
//##################################################################
//                      DESTRUCTORS
//##################################################################
//

SymFun::~SymFun()
{
    destroy();
}

void SymFun::destroy()
{
    int i;
    if(constructorString != 0) delete [] constructorString;

    if(variableNames != 0)
    {
    for(i =0; i < variableCount; i++) delete [] variableNames[i];
    delete [] variableNames;
    }

    if(constantNames != 0)
    {
    for(i =0; i < constantCount; i++) delete [] constantNames[i];
    delete [] constantNames;
    delete [] constantValues;
    }

    if(evaluationData != 0) delete [] evaluationData;
    if(executionArray != 0) delete [] executionArray;

    if(sNames         != 0)
    {
    for(i=0; i< symbolCount; i++) if(sNames[i] != 0) delete [] sNames[i];
    delete [] sNames;
    }

    constructorString = 0;

    variableNames     = 0;
    variableCount     = 0;

    constantNames     = 0;
    constantCount     = 0;
    constantValues    = 0;

    symbolCount       = 0;
    sNames            = 0;

    evaluationData     = 0;
    evaluationDataSize = 0;

    executionArray     = 0;
    executionArraySize = 0;

    LibFunctions       = 0;

}
//
//##################################################################
//                      INITIALIZATION
//##################################################################
//
/**
  Initializes a SymFun instance
  to a null SymFun.
*/
int SymFun::initialize()
{
    destroy();
    return 0;
}
/**
Initialize an SymFun instance to one
of a single variable, x, where the function is
specified by the null terminated string S. If the initialization fails,
error diagnostics are output to the standard error stream
(cerr) and the program returns an error value. 

@arg S: Null terminated character string in the variable x that 
specifies the function.

@returns 0 (= no error) 1 (= error). 
*/

int SymFun::initialize(char const* S)
{
    destroy();
    const char*V []  = {"x"};
    int Vcount = 1;

    const char** C        = 0;
    int Ccount            = 0;
    const double* Cvalues = 0;
    
    int  cReturn;
    cReturn = create(V,Vcount,C,Ccount, Cvalues, S);
    if(cReturn != 0) return cReturn;
    return 0;
}
/**
Initializes a SymFun instance to one
of Vcount variables from the initialization string S. 
S is a null terminated character string. If the initialization fails,
error diagnostics are output to the standard error stream
(cerr) and the program returns an error value. 

@arg V      : Array of null terminated strings specifying independent variable names
@arg Vcount : The number of independent variables
@arg S      : Null terminated character string specifying the function

@returns 0 (= no error) 1 (= error). 

Sample specification and use of a function of two variables x and y: 

\code
SymFun F;              // Create null instance
int Vcount = 2;                     // number of independent variables
char*V []  = {"x","y"};             // x,y  = independent variable names
char*S     = "x^2 + 2*y";           // specify a function 
     
int ierr = F.initialize(V,Vcount,S);// initialize 
if(ierr != 0) 
{
cerr << "Initialization of SymFun Failed" << endl;
exit(1);
}

    
cout << F(2.0,3.0) << endl;        // evaluate and output result at (x,y) = (2.0,3.0) 
\endcode
*/


int SymFun::initialize(const char** V, int Vcount, char const* S)
{
    destroy();
    const char** C  = 0;
    int Ccount      = 0;
    double* Cvalues = 0;
    int  cReturn;
    cReturn = create(V,Vcount,C,Ccount, Cvalues, S);
    if(cReturn != 0) return cReturn;
    return 0;
}
/**
Initializes a SymFun instance to one of Vcount variables and
Ccount symbolic constants from the initialization string S. 
If the initialization fails, error diagnostics are output to the 
standard error stream (cerr) and the program returns an error value. 
  
@arg V      : Array of null terminated strings specifying independent variable names
@arg Vcount : The number of independent variables
@arg S      : Null terminated character string specifying the function
@arg V      : Array of null terminated strings specifying symbolic constant names
@arg Ccount : The number of symbolic constants 
@arg Cvalues: The values of the symbolic constants
@arg S      : Null terminated character string specifying the function

Sample:
\code
//
//  Initializes a CAMsymbolic function instance to one that implements
//  a*x^2 + b*x + c; a, b, c being symbolic constants.
//
    SymFun f;                       // create instance
     
    int Vcount       = 1;                        // number of independent variables
    char*V []        = {"x"};                    // specify variable name
    int Ccount       = 3;                        // number of symbolic constants
    char*C []        = {"a","b","c"};            // specify constant names
    double Cvalues[] = {1.0, 2.0, 1.0};          // initial values of a,b,c
    char* S = "a*x^2 + b*x + c";                 // initialization string

    int ierr = f.initialize(V,Vcount,C,Ccount,Cvalues, S);
    if(ierr != 0) 
    {
    cerr << "Initialization of SymFun Failed" << endl;
    exit(1);
    }

    cout << f << endl << endl;                    // print out function

    cout << "The value of the function at x = 1.0 is " 
         << f(1.0) << endl << endl;

    f.setConstantValue("a",2.0);                  // reset the symbolic constant
                                                  // a to have the value 2.0
    cout << f << endl << endl;                    // print out function

    cout << "The value of the function at x = 1.0 is  " 
         << f(1.0) << endl;
\endcode
*/
int  SymFun::initialize(const char** V, int Vcount, const char** C,
int Ccount, double const* Cvalues, char const* S)
{
    destroy();
    int  cReturn;
    cReturn = create(V,Vcount,C,Ccount, Cvalues, S);
    if(cReturn != 0) return cReturn;
    return 0;
}

/**
  Initializes the SymFun instance with F
*/

int SymFun::initialize(const SymFun& F)
{
    destroy();
//
//  Allocate Storage and Initalize
//
    int i;
    if(F.constructorString != 0)
    {
    constructorString = new char[strlen(F.constructorString) + 1];
    strcpy(constructorString,F.constructorString);
    }

    if(F.variableCount != 0)
    {
    variableNames  = new char*[F.variableCount];
    variableCount  = F.variableCount;

    for(i = 0; i < F.variableCount; i++)
    {
    variableNames[i] = new char[strlen(F.variableNames[i]) + 1];
    strcpy(variableNames[i],F.variableNames[i]);
    }
    }

    if(F.constantCount != 0)
    {
    constantNames  = new char*[F.constantCount];
    constantCount  = F.constantCount;
    constantValues = new double[F.constantCount];

    for(i = 0; i < F.constantCount; i++)
    {
    constantNames[i] = new char[strlen(F.constantNames[i]) + 1];
    strcpy(constantNames[i],F.constantNames[i]);
    constantValues[i] = F.constantValues[i];
    }
    }

    evaluationDataSize = F.evaluationDataSize;

    if(F.evaluationData != 0)
    {
    evaluationData     = new double[evaluationDataSize];
    for(i=0; i< evaluationDataSize; i++)
    {
    evaluationData[i] = F.evaluationData[i];
    }}

    executionArraySize = F.executionArraySize;
    
    if(F.executionArray != 0)
    {
    executionArray     = new long[executionArraySize];
    for(i=0; i< executionArraySize; i++)
    {
    executionArray[i] = F.executionArray[i];
    }}

    symbolCount = F.symbolCount;
    sNames      = new char*[symbolCount];
    for(i=0; i< symbolCount; i++)
    {
    sNames[i] = new char[strlen(F.sNames[i])+1];
    strcpy(sNames[i],F.sNames[i]);
    }

    LibFunctions       = CAMrealOperatorLib::getFunctionArrayPtr();
    return 0;
}
/** Assignment operator. The instance is intialized using F. The
    data associated with the original instance is destroyed.  
*/
void SymFun::operator=(const SymFun& F)
{
    initialize(F);
}

long SymFun::getSymbolCount() const
{
    return symbolCount;
}
//
//##################################################################
//                      OUTPUT
//##################################################################
//
/**
 Outputs the initialization string, the variable names, the symbolic 
 constant names and the symbolic constant values.
*/
ostream&  operator <<(ostream& out_stream, const SymFun& F)
{
    int i;
     out_stream << F.getConstructorString() << endl;
    out_stream << " Variables : " << endl;

    for(i = 0; i < F.getVariableCount(); i++)
    {
    out_stream << F.getVariableName(i) << endl;
    }

    if(F.getConstantCount() > 0)
    {
    out_stream << " Constant Values : " << endl;
    for(i = 0; i < F.getConstantCount(); i++)
    {
    out_stream << F.getConstantName(i) << "  " << F.getConstantValue(i) << endl;
    }}

return out_stream;

}
//
//##################################################################
//                      MEMBER FUNCTIONS
//##################################################################
//
/**
 Returns the string used to initialize the SymFun.
 */
 
char* SymFun::getConstructorString() const
{
    return constructorString;
}
/**
 Returns the number of variables associated with the SymFun.
*/
int SymFun::getVariableCount() const
{
      return variableCount;
}

/**
Returns the name of the ith variable associated with the 
SymFun.
*/
char*  SymFun::getVariableName(int i) const
{
      return variableNames[i];
}
/**
Returns the number of symbolic constants associated with the 
SymFun.
 */
int SymFun::getConstantCount() const
{
      return constantCount;
}
/**
 Returns the name of the ith symbolic constant associated 
 with the SymFun.
*/
char*  SymFun::getConstantName(int i) const
{
      return constantNames[i];
}
/**
 Returns the value of the ith symbolic constant 
 associated with the SymFun.
*/
double  SymFun::getConstantValue(int i) const
{
      return constantValues[i];
}
/**
 Returns the value of the ith symbolic constant 
 associated with the SymFun.
 
 @arg S: Character string with name of the symbolic constant.
 @arg x: Double value specifying the new value of the constant.
*/
void  SymFun::setConstantValue(const char* S,double x)
{
    int i;
    for(i =0; i < constantCount; i++)
    {
    if(strcmp(S,constantNames[i]) == 0) constantValues[i] = x;
    }
    setConstantEvaluationData();
}

char** SymFun::getVariableNamePtr() const
{
    return variableNames;
}

char** SymFun::getConstantNamePtr() const
{
    return constantNames;
}

double* SymFun::getConstantValuePtr() const
{
    return  constantValues;
}
void  SymFun::initializeEvaluationData(const expressionTransform& T)
{
    long symbolCount = T.getSymbolCount();
    char**sNames     = T.getSymbolNamesPtr();
    int i;  int j;

    if(variableCount != 0)
    for(i = 0; i < variableCount; i++)
    evaluationData[i] = 0.0;

    for(i = variableCount,j = 0; i < variableCount + constantCount; i++,j++)
    evaluationData[i] = constantValues[j];

    for(i = variableCount + constantCount; i < symbolCount; i++)
    {evaluationData[i] = atof(sNames[i]);}

}

void  SymFun::initializeExecutionArray(const expressionTransform& T)
{
    long* executionArrayPtr = T.getExecutionArrayPtr();
    int i;
    for(i=0; i < executionArraySize; i++)
    {executionArray[i] = executionArrayPtr[i];
    }
}

void  SymFun::setConstantEvaluationData()
{
    int i; int j;

    for(i = variableCount,j = 0; i < variableCount + constantCount; i++,j++)
    evaluationData[i] = constantValues[j];
}

/**
 Returns the value of the SymFun
 using the variable value x. 
*/
double SymFun::operator()(double x) const
{
    if(variableCount != 1) argError(1, variableCount);
    evaluationData[0] = x;
    return evaluate();
}

/**
 Returns the value of the SymFun
 using the variable value (x1,x2). 
*/
double SymFun::operator()(double x1, double x2) const
{
    if(variableCount != 2) argError(2, variableCount);

    evaluationData[0] = x1;
    evaluationData[1] = x2;
    return evaluate();

}

/**
 Returns the value of the SymFun
 using the variable value (x1,x2,x3). 
*/

double SymFun::operator()(double x1, double x2, double x3) const
{
     if(variableCount != 3) argError(3, variableCount);

    evaluationData[0] = x1;
    evaluationData[1] = x2;
    evaluationData[2] = x3;
    return evaluate();
}

/**
 Returns the value of the SymFun
 using the variable value (x1,x2,x3,x4). 
*/

double SymFun::operator()(double x1, double x2, double x3, double x4) const
{
     if(variableCount != 4) argError(4, variableCount);

    evaluationData[0] = x1;
    evaluationData[1] = x2;
    evaluationData[2] = x3;
    evaluationData[3] = x4;
    return evaluate();
}

/**
 Returns the value of the SymFun using the
 n variable values in the <vector>double x.
 @arg x vector<double> array of values
*/
double SymFun::operator()(const vector<double>& x) const
{
	int n = x.size();
    if(variableCount != n) argError(n, variableCount);

    int i;
    for(i = 0; i < n; i++) evaluationData[i] = x[i];
    return evaluate();
}

/**
 Returns the value of the SymFun using the
 n variable values in the double array x.
 @arg x poiner to a double array
 @arg n the number of elements in x
*/
double SymFun::operator()(double*x, int n) const
{
     if(variableCount != n) argError(n, variableCount);

    int i;
    for(i = 0; i < n; i++) evaluationData[i] = x[i];
    return evaluate();
}

void SymFun::argError(int argC, int vCount)
{
    cerr << " Incorrect Number of Arguments in SymFun " << endl;
    cerr << " Called with " << argC << " arguments, expecting " << vCount;
    CAMsymExit();
}

double SymFun::evaluate() const
{
    int j;
    double* argData[10];   // limit of 10 args for now

    int functionIndex;
    int argCount;

    int executionIndex = 0;
    while(executionIndex < executionArraySize)
    {
    functionIndex = executionArray[executionIndex]; executionIndex++;
    argCount      = executionArray[executionIndex]; executionIndex++;
    for(j =0; j < argCount; j++)
    {
    argData[j] = &(evaluationData[executionArray[executionIndex]]);
    executionIndex++;
    }
    ((void(*)(double**))LibFunctions[functionIndex])(argData);
    }

    return evaluationData[evaluationDataSize - 1];
}

/*
 void SymFun::createCcode()
 {
    CAMrealOperatorLib L;
    
    int binaryPlusIndex   = L.getBinaryOperatorIndex("+");
    int binaryMinusIndex  = L.getBinaryOperatorIndex("-");
    int binaryTimesIndex  = L.getOperatorIndex("*");
    int binaryDivideIndex = L.getOperatorIndex("/");
    int binaryExpoIndex   = L.getOperatorIndex("^");
    
 	printf("//  \n");
 	printf("// %s \n",getConstructorString());
 	printf("// \n");
 	
 	printf("    double evalData[%d]; \n\n",evaluationDataSize);
 	//
 	// output variable initializations
 	//
 	int i; int j;
 	if(variableCount != 0)
    for(i = 0; i < variableCount; i++)
    {
    	printf("    evalData[%d] = %s; \n",i,getVariableName(i));
    }
    
    for(i = variableCount,j = 0; i < variableCount + constantCount; i++,j++)
    {
    	printf("    evalData[%d] = %s; \n",i,getConstantName(j));
    }
    
    for(i = variableCount + constantCount; i < symbolCount; i++)
    {
    	printf("    evalData[%d] = %s; \n",i,sNames[i]);
    }
 	//
 	// output evaluation code
 	
    int argDataIndex[10];   // limit of 10 args for now

    int functionIndex;
    int argCount;

    int executionIndex = 0;
    while(executionIndex < executionArraySize)
    {
    functionIndex = executionArray[executionIndex]; executionIndex++;
    
    //printf("%s \n",L.getOperatorSymbol(functionIndex));
    
    argCount      = executionArray[executionIndex]; executionIndex++;
    
    for(j =0; j < argCount; j++)
    {
    argDataIndex[j] = executionArray[executionIndex];
    executionIndex++;
    }
    
    printf("    evalData[%d] = ",argDataIndex[argCount-1]);
    if(argCount == 2) // unary operator
    {
    	printf("%s(evalData[%d]); \n",L.getOperatorSymbol(functionIndex),
    	argDataIndex[0]);
    }
    else
    {
    	if(	(functionIndex == binaryPlusIndex)||
       		(functionIndex == binaryMinusIndex)||
       		(functionIndex == binaryTimesIndex)||
       		(functionIndex == binaryDivideIndex))
    	{
    	printf("evalData[%d] %s evalData[%d];\n",
    	argDataIndex[0],L.getOperatorSymbol(functionIndex),argDataIndex[1]);
    	}
    	else
    	{
    	if(functionIndex != binaryExpoIndex)
    	{
    		printf("%s(",L.getOperatorSymbol(functionIndex));
    	    printf("evalData[%d],evalData[%d]);\n", argDataIndex[0],argDataIndex[1]);
    	}
    	else
    	{
    		printf("pow(");
    	    printf("evalData[%d],evalData[%d]);\n", argDataIndex[0],argDataIndex[1]);
    	}
    	}
    }
    
    //((void(*)(double**))LibFunctions[functionIndex])(argData);
    }
    
	printf("    return evalData[%d]; \n",evaluationDataSize - 1);
    return;
 }
*/


