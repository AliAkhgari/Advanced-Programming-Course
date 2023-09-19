#ifndef __SOCIAL_BOT_H__
#define __SOCIAL_BOT_H__ "__SOCIAL_BOT_H__"

#include <string>
#include <vector>
#include <iostream>
#include "Bot.hpp"
#include "Channel.hpp"
#include "EchoBot.hpp"
#include "LoggerBot.hpp"
#include "FredBot.hpp"
#include "LibrarianBot.hpp"
#include "ChannelAlreadyExist.hpp"
#include "ChannelDoesntExist.hpp"
#include "SameSrcDest.hpp"

typedef std::string Name;

class SocialBots
{
private:
    std::vector < Bot* > bots;
    std::vector < Channel* > channels;

public:
    void add_channel(Name name);

    void add_echo_bot(Name src_channel, Name dest_channel);

    void add_logger_bot(Name filename);

    void add_fred_bot(Name channel);

    void add_librarian_bot(Name channel);
    
    void tell(Name channel, std::string message);

    Channel* find_channel_by_name(Name name);

    void add_logger_bot_to_current_channels(LoggerBot* logger_bot);

    bool is_channel_exists(Name channel);

};


#endif