#ifndef __FRED_BOT_H__
#define __FRED_BOT_H__ "__FRED_BOT_H__"

#include "Bot.hpp"
#include "Channel.hpp"
#include <string>

typedef std::string Name;

class FredBot : public Bot
{
private:
    Channel* channel;

public:
    FredBot(Channel* channel_)
    {
        channel = channel_;
    }
    
    virtual void notify (std::string message)
    {
        if(message == "Hi")
            channel->send_message("Hello");
    }
    
};


#endif