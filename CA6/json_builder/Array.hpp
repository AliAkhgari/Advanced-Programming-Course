#ifndef __ARRAY_H__
#define __ARRAY_H__ "__ARRAY_H__"

#include <vector>
#include <string>
#include "Data.hpp"
#include "Int.hpp"
#include "String.hpp"

#define OPEN_BRACKET "["
#define CLOSE_BRACKET "]"

class Array : public Data
{

private:
    int parentId;
    int id; 
    std::string key;    

public:
    Array(int parentId_, int id_, std::string key_)
    : Data(parentId_)
    {
        id = id_;
        key = key_;
    }

    virtual void print () 
    {
        std::string array_key = "\"" + key + "\"" + ": " + OPEN_BRACKET;
        if(key == "")
            std::cout << OPEN_BRACKET;
        else
            std::cout << array_key;
    }

    virtual void printContainerSign()
    {
        std::cout << CLOSE_BRACKET;
    }

    virtual std::string getKey () { return key; }

    virtual int getId () { return id; }
};



#endif