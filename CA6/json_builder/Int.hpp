#ifndef __INT__
#define __INT__ "__INT__"

#include <iostream>
#include "Data.hpp"

class Int : public Data
{
private:
    int parentId;
    int value;

public:
    Int(int parentId_, int value_)
    : Data(parentId_)
    {
        value = value_;
    }

    virtual void print()
    {
        std::cout << value;
    }

    virtual std::string getKey () { return ""; }

    virtual int getId () { return -1; }

    virtual void printContainerSign() {}
};






#endif