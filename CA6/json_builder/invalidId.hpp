#ifndef __INVALID_ID_H__
#define __INVALID_ID_H__ "__INVALID_ID_H__"

#include "exception"
#include <string>

class InvalidId : public std::exception
{
private:
    std::string exceptionMessage = "Invalid id.\n";

public:
    virtual const char* what() const throw ()
    {
        return exceptionMessage.c_str();
    }
};





#endif