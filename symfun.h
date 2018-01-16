//
//##################################################################
//  		       CAM SYMBOLIC FUNCTION
//##################################################################
//
//	                                Chris Anderson 9/10/96 (C) UCLA
//
//
// CRA 05/15/01 :  Added operator = :  
// CRA 01/25/07 :  Made constructors/initializers const correct
//                 and added documentation to the source file. 
// CRA 02/21/07 :  Additional changes to const. 

#include <iostream>
#include <functional>
#include <vector>
using namespace std;

#ifndef  __SYMBOLIC_FUNCTION__
#define  __SYMBOLIC_FUNCTION__

#include "symfunimpexp.h"

#ifndef  __EXPRESSION_TRANSFORM__
class expressionTransform;
#endif

class __IMPEXP__ SymFun
{

public  :

    SymFun();
    SymFun(const SymFun& F);

    //
    // Modifications Dec. 23, 2016
    //
    //###############################################
    //   Alternate constructors and initializers
    //###############################################
    //
    SymFun(const string& S)
    {
    	 initialize(S);
    }

    SymFun(const vector<string> V, const string& S)
    {
    	initialize(V,S);
    }

    SymFun(const vector<string> V, const vector<string> C, const vector<double> Cvalues, const string& S)
    {
    	initialize(V,C,Cvalues,S);
    }

    int initialize(const string& S)
    {
    	return initialize(S.c_str());
    }

    int initialize(const vector<string> V, const string& S)
    {
    	int Vcount = V.size();
    	vector<const char*> Varray(Vcount);
    	for(int i = 0; i < Vcount; i++)
    	{
    		Varray[i] = V[i].c_str();
    	}
    	return initialize(&Varray[0],Vcount,S.c_str());
    }

    int initialize(const vector<string> V, const vector<string> C, const vector<double> Cvalues, const string& S)
    {
    	int Vcount = V.size();
    	vector<const char*> Varray(Vcount);
    	for(int i = 0; i < Vcount; i++)
    	{
    		Varray[i] = V[i].c_str();
    	}

    	int Ccount = C.size();
    	vector<const char*> Carray(Ccount);
    	for(int i = 0; i < Ccount; i++)
    	{
    		Carray[i] = C[i].c_str();
    	}
    	return initialize(&Varray[0],Vcount,&Carray[0],Ccount,&Cvalues[0],S.c_str());
    }

    //###############################################
    //  Anonyomous function pointers and mutatators
    //###############################################


//  Returns a std::function that is bound to the evaluation operator of *this

#if __cplusplus > 199711L
	std::function<double(double)> getEvaluationPtr1d() const
	{
	std::function<double(double)> F = [this](double x1) {return this->operator()(x1);};
	return std::move(F);
	}
#endif

#if __cplusplus > 199711L
	std::function<double(double,double)> getEvaluationPtr2d() const
	{
	std::function<double(double,double)> F = [this](double x1,double x2) {return this->operator()(x1,x2);};
	return std::move(F);
	}
#endif

#if __cplusplus > 199711L
	std::function<double(double,double,double)> getEvaluationPtr3d() const
	{
	std::function<double(double,double,double)> F = [this](double x1,double x2,double x3) {return this->operator()(x1,x2,x3);};
	return std::move(F);
	}
#endif

#if __cplusplus > 199711L
	std::function<double(double,double,double,double)> getEvaluationPtr4d() const
	{
	std::function<double(double,double,double,double)> F = [this](double x1,double x2,double x3,double x4) {return this->operator()(x1,x2,x3,x4);};
	return std::move(F);
	}
#endif


#if __cplusplus > 199711L
	std::function<double(vector<double>&)> getEvaluationPtrNd() const
	{
	std::function<double(vector<double>&)> F = [this](vector<double>& x) {return this->operator()(x);};
	return std::move(F);
	}
#endif


    void setConstantValue(const string& C,double x)
    {
    	setConstantValue(C.c_str(),x);
    }

    //###############################################
    //
    //###############################################
    //

    SymFun(char const* S);
    SymFun(const char** V, int Vcount, char const* S);
    SymFun(const char** V, int Vcount, const char** C, int Ccount,
    double const* Cvalues, char const* S);

    ~SymFun();

    int  initialize();
    int  initialize(char const* S);
    int  initialize(const SymFun& F);
    int  initialize(const char** V, int Vcount, char const* S);
    int  initialize(const char** V, int Vcount, const char** C, int Ccount,
    double const* Cvalues,char const* S);

    void operator=(const SymFun& F);

	 __IMPEXP__ friend ostream& operator <<(ostream& out_stream, const SymFun& F);

    char*  getConstructorString() const;
    int    getVariableCount() const;
    char*  getVariableName(int i) const;
    int    getConstantCount() const;
    char*  getConstantName(int i) const;
    double getConstantValue(int i) const;
    void   setConstantValue(const char* S,double x);

    long   getSymbolCount() const;
    char   **sNames;

    double operator()(double x) const;
    double operator()(double x1, double x2) const;
    double operator()(double x1, double x2, double x3) const ;
    double operator()(double x1, double x2, double x3, double x4) const;

    double operator()(double*x, int n)   const;
    double operator()(const vector<double>& x) const;


public  :

    char*       constructorString;

    char**      variableNames;
    int         variableCount;

    char**      constantNames;
    int         constantCount;
    double*     constantValues;

    long        symbolCount;      // total number of variables, symbolic constants, 
                                  // and numeric constants 

    long*       executionArray;
    long        executionArraySize;

    double*     evaluationData;
    long        evaluationDataSize;

    double evaluate() const;

    char**  getVariableNamePtr() const;
    char**  getConstantNamePtr() const;
    double* getConstantValuePtr() const;

    void destroy();
    int create(const char**V, int Vcount, const char**C, int Ccount, 
               double const* Cvalues, char const* S);

    void        initializeEvaluationData(const expressionTransform& T);
    void        initializeExecutionArray(const expressionTransform& T);
    void        setConstantEvaluationData();


    void** LibFunctions;

    static void argError(int argC, int vCount);
    
    /* void createCcode(); // experimenting 02/19/07 */

};

#endif




