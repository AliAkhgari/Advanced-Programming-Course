#ifndef __GET_H__
#define __GET_H__ "__GET_H__"

#include <string>
#include <iostream>
#include "UTRIP.hpp"

class GET
{
private:
    std::vector <std::string> commands;
    UTRIP* utrip;
    
public:
    GET(UTRIP* utrip_, std::vector <std::string> commands_);

    bool is_have(std::string kind);

    std::string find_value(std::string kind);

    void read_command();
};


#endif