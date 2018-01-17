//
//##################################################################
//  		   CLASS  ExpressionTransform  Header
//##################################################################
//
//	                               
// Version 1/22/2009                 Chris Anderson 9/10/96 (C) UCLA
//
#ifndef  __EXPRESSION_TRANSFORM__
#define  __EXPRESSION_TRANSFROM__

namespace SCC
{

#ifndef  _OPERATOR_LIB__
class OperatorLib;
#endif

class  ExpressionTransform
{
    public :

    ExpressionTransform();
    ExpressionTransform(const ExpressionTransform& E);
 
    ExpressionTransform(char** V, int Vcount, char* S, OperatorLib* O);
    ExpressionTransform(char** V, int Vcount, char** C, int Ccount,
                        char* S,OperatorLib* O);

    ~ExpressionTransform();

    int initialize();
    int initialize(char** V, int Vcount, char* S, OperatorLib* O);
    int initialize(char** V, int Vcount, char** C, int Ccount, char* S,
                    OperatorLib* O);

    void destroy();

    int createTransform(char** V, int Vcount, char** C, int Ccount, char* S);



    char** getSymbolNamesPtr()     const {return sNames;};
    long   getSymbolCount()        const {return symbolCount;};
    long   getEvaluationDataSize() const {return evaluationDataSize;};
    long*  getExecutionArrayPtr()  const {return executionArray;};
    long   getExecutionArraySize() const {return executionArraySize;};

//
//  Internal Data Storage
//
    private :

    int         variableCount;
    int         constantCount;

    char**      sNames;
    long        symbolCount;

    long*       executionArray;
    long        executionArraySize;

    long        evaluationDataSize;

    SCC::OperatorLib* opLib;

    enum{DELIM = -2, VAR   =-1, NOOP   = 0};
    enum{LEFTP = -1, COMMA = 0, RIGHTP = 1};

    int separateIntoTokens(char* inputS, char* outputS);

    int  encodeExpression(char* inputS,long Ssize,char** sNames,
    long vCount, long cCount, long sCount,long* expressionCode,
    long& expressionCodeSize);

    int setupEvaluation(long* eCode, int iStart, int iEnd,
    long* execArray, long& execIndex, long& dIndex);
    
    void errorHandler();

};
} // namespace
#endif

