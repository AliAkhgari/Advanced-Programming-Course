#ifndef __DUPLICATE_KEY_H__
#define __DUPLICATE_KEY_H__ "__DUPLICATE_KEY_H__"

#include "exception"
#include <string>

class DuplicateKey: public std::exception
{
private:
    std::string exceptionMessage = "Duplicate key.\n";

public:
    virtual const char* what() const throw ()
    {
        return exceptionMessage.c_str();
    }
};






#endif