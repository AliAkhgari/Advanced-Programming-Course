#ifndef __CHANNEL_ALREADY_EXIST_H__
#define __CHANNEL_ALREADY_EXIST_H__ "__CHANNEL_ALREADY_EXIST_H__"

#include "exception"
#include <string>

class ChannelAlreadyExist : public std::exception
{
private:
    std::string exceptionMessage = "Channel already exist\n";//__________****___________
    
public:
    virtual const char* what() const throw ()
    {
        return exceptionMessage.c_str();
    }
};


#endif