#include <exception>
#include <stdexcept>
#include <string>

/*
#############################################################################
#
# Copyright 1996-2019 Chris Anderson
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# For a copy of the GNU General Public License see
# <http://www.gnu.org/licenses/>.
#
#############################################################################
*/

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
