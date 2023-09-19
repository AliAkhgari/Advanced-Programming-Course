#ifndef __LOGGER_BOT_H__
#define __LOGGER_BOT_H__ "__LOGGER_BOT_H__"

#include "Bot.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

typedef std::string Name;

class LoggerBot : public Bot
{
private:
    Name filename;
    
public:
    LoggerBot(Name filename_)
    {
        filename = filename_;
    }

    virtual void notify (std::string message)
    {
        std::ofstream output(filename, std::ios_base::app);
        output << message << std::endl;
    }

};



#endif