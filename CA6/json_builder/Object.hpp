#ifndef __OBJECT_H__
#define __OBJECT_H__ "__OBJECT_H__"

#include <string>
#include <iostream>
#include <vector>
#include "Data.hpp"
#include "KeyString.hpp"
#include "KeyInt.hpp"

#define OPEN_BRACE "{"
#define CLOSE_BRACE "}"

class Object : public Data
{
private:

    int parentId;
    int id; 
    std::string key;
    
public:

    Object(int parentId_, int id_, std::string key_)
    : Data(parentId_)
    {
        parentId = parentId_;
        id = id_;
        key = key_;
    }

    virtual void print() 
    {
        std::string objectKey = "\"" + key + "\"" + ": " + OPEN_BRACE;
        if(key == "")
            std::cout << OPEN_BRACE;
        else
            std::cout << objectKey;
    }

    virtual void printContainerSign()
    {
        std::cout << CLOSE_BRACE;
    }
    
    virtual std::string getKey () { return key; }

    virtual int getId () { return id; }
    
};



#endif