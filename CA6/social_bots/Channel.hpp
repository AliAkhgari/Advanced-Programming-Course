#ifndef __CHANNEL_H__
#define __CHANNEL_H__ "__CHANNEL_H__"

#include "Bot.hpp"
#include <string>
#include <vector>

class Channel
{
private:
    std::string name;
    std::vector < std::string > messages;
    std::vector < Bot* > joined_bot;

public:
    Channel(std::string name_)
    {
        name  = name_;
    }

    std::string get_name () { return name; }

    void send_message(std::string message);

    void add_bot_to_channel(Bot* bot);

    void notify_joined_bot(std::string message);

};


#endif