#ifndef __CHANNEL_DOESNT_EXIST_H__
#define __CHANNEL_DOESNT_EXIST_H__ "__CHANNEL_DOESNT_EXIST_H__"

#include "exception"
#include <string>

class ChannelDoesntExist : public std::exception
{
private:
    std::string exceptionMessage = "Channel does not exist\n";
    
public:
    virtual const char* what() const throw ()
    {
        return exceptionMessage.c_str();
    }
};


#endif