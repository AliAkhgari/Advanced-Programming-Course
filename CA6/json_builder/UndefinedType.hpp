#ifndef __UNDEFINED_TYPE_H__
#define __UNDEFINED_TYPE_H__ "__UNDEFINED_TYPE_H__"

#include "exception"
#include <string>

class UndefinedType: public std::exception
{
private:
    std::string exceptionMessage = "Undefined type.\n";

public:
    virtual const char* what() const throw ()
    {
        return exceptionMessage.c_str();
    }
};


#endif