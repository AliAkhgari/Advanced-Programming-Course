#ifndef __DELETE_H__
#define __DELETE_H__ "__POST_H__"

#include <string>
#include <iostream>
#include "UTRIP.hpp"

class DELETE
{
private:
    UTRIP* utrip;
    std::vector <std::string> commands;

public:
    DELETE(UTRIP* utrip_, std::vector <std::string> commands_);

    std::string find_value(std::string kind);

    void read_command();
};


#endif
 