#ifndef __SAME_SRC_DEST_H__
#define __SAME_SRC_DEST_H__ "__SAME_SRC_DEST_H__"

#include "exception"
#include <string>

class SameSrcDest : public std::exception
{
private:
    std::string exceptionMessage = "Source and destination cannot be the same channel\n";
public:
    virtual const char* what() const throw ()
    {
        return exceptionMessage.c_str();
    }
};


#endif