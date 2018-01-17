#include <exception>
#include <stdexcept>
#include <string>

#ifndef  _SymFunException_
#define  _SymFunException_
namespace SCC
{
class SymFunException : public std::runtime_error
{
public:

   SymFunException ()
  : runtime_error("SymFun error"),
  errorMessage("SymFun error"),errorInfo(""),offendingString("")
  {
	 setErrorReturn();
  }

  SymFunException (const std::string& msg, const std::string& errInfo, const std::string& offString)
  : runtime_error("SymFun error"),
  errorMessage(msg),errorInfo(errInfo), offendingString(offString)
  {
  setErrorReturn();
  }

  virtual ~SymFunException () throw() {}

  virtual const char* what() const throw()
  {
    return errorReturn.c_str();
  }


  std::string getErrorMessage()      const { return errorMessage;};
  std::string getErrorInformation () const { return errorInfo;};
  std::string getOffendingString  () const { return offendingString;}

  void setErrorReturn()
  {
	errorReturn =  errorMessage + "\n" +  errorInfo + "\n" +  offendingString + "\n";
  }

  std::string errorMessage;
  std::string errorInfo;
  std::string offendingString;

  std::string errorReturn;
};
}
#endif
