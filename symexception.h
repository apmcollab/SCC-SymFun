#include <exception>
#include <stdexcept>

/*
try {
    ComplexOperationThatCouldFailABunchOfWays();
} catch (std::exception& e) {
    cerr << e.what() << endl;
}
*/
class SymFunException : public runtime_error 
{
public:

  SymFunException ("Error message ?")
    : runtime_error( "SymFun error" )
    {}


  virtual const char* what() const throw()
  {
    cnvt.str( "" );

    cnvt << runtime_error::what() << ": " << getNumerator()
         << " / " << getDenominator();

    return cnvt.str().c_str();
  }


};
