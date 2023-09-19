#ifndef __ECHO_BOT_H__
#define __ECHO_BOT_H__ "__ECHO_BOT_H__"

#include "Bot.hpp"
#include "Channel.hpp"
#include <string>

typedef std::string Name;

class EchoBot : public Bot
{
private:
    Channel* src_channel;
    Channel* dest_channel;

public:
    EchoBot(Channel* src_channel_, Channel* dest_channel_)
    {
        src_channel = src_channel_;
        dest_channel = dest_channel_;
    }

    virtual void notify (std::string message)
    {
        dest_channel->send_message(message);
    }

};



#endif