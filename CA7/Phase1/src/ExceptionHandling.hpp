#ifndef __EXCEPTION_HANDLING_H__
#define __EXCEPTION_HANDLING_H__ "__EXCEPTION_HANDLING_H__"

#include "exception"
#include <string>

class ExceptionHandling : public std::exception
{
private:
    std::string exception_message;

public:
    ExceptionHandling(std::string exception_message_)
    {
        exception_message = exception_message_;
    }

    virtual const char* what() const throw ()
    {
        return exception_message.c_str();
    }
};


#endif