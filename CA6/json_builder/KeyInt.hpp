#ifndef __KEY_INT_H__
#define __KEY_INT_H__ "__KEY_INT_H__"

#include <iostream>
#include <string>
#include "Data.hpp"

class KeyInt : public Data
{
private:
    int parentId;
    std::string key;
    int value;

public:
    KeyInt(int parentId_, std::string key_, int value_)
    : Data(parentId_)
    {
        parentId = parentId_;
        key = key_;
        value = value_;
    }

    virtual void print ()
    {
        std::cout << "\"" << key << "\"" << ": " << value;
    }

    virtual std::string getKey () { return ""; }

    virtual int getId () { return -1; }

    virtual void printContainerSign() {}
};



#endif