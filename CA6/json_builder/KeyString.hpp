#ifndef __KEY_STRING_H__
#define __KEY_STRING_H__ "__KEY_STRING_H__"

#include <string>
#include <iostream>
#include "Data.hpp"

class KeyString : public Data
{
private:

    int parentId;
    std::string key;
    std::string value;
    
public:

    KeyString(int parentId_, std::string key_, std::string value_)
    : Data(parentId_)
    {
        parentId = parentId_;
        key = key_;
        value = value_;
    }

    virtual void print ()
    {
        std::cout << "\"" << key << "\"" << ": " << "\"" << value << "\"";
    }

    virtual std::string getKey () { return ""; }

    virtual int getId () { return -1; }

    virtual void printContainerSign() {}
};


#endif