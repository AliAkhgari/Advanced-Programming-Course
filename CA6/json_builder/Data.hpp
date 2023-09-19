#ifndef __DATA_H__
#define __DATA_H__ "__DATA_H__"

#include <string>

class Data
{
private:
    int parentId;
public:
    Data(int parentId_)
    {
        parentId = parentId_;
    }
    
    int getParentId () { return parentId; }
    
    bool printed = false;
    
    std::string dataType;

    virtual void print () = 0;

    virtual std::string getKey () = 0;

    virtual int getId () = 0;

    virtual void printContainerSign () = 0;
    
};



#endif