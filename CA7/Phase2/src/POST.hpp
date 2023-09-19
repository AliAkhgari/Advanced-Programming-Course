#ifndef __POST_H__
#define __POST_H__ "__POST_H__"

#include <string>
#include <iostream>
#include "UTRIP.hpp"

class POST
{
private:
    UTRIP* utrip;
    std::vector <std::string> commands;

public:
    POST(UTRIP* utrip_, std::vector <std::string> commands_);
    
    bool is_have(std::string kind);

    std::string find_value(std::string kind);

    std::string find_city_name();

    std::string filter_type();

    void read_command();

};





#endif