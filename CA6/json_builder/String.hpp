#ifndef __STRING__
#define __STRING__ "__STRING__"

#include <string>
#include <iostream>
#include "Data.hpp"

class String : public Data
{
private:

    int parentId;
    std::string value;

public:

    String(int parentId_, std::string value_)
    : Data(parentId_)
    {
        value = value_;
    }

    virtual void print()
    {
        std::cout << "\"" << value << "\"";
    }

    virtual std::string getKey () { return ""; }

    virtual int getId () { return -1; }

    virtual void printContainerSign() {}
};




#endif