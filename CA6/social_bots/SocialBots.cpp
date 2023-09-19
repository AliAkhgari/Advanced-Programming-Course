#include "SocialBots.hpp"

using namespace std;

void SocialBots::add_channel(Name name)
{
    try
    {
        if(is_channel_exists(name))
            throw ChannelAlreadyExist();

        Channel* channel = new Channel(name);
        channels.push_back(channel);
    }
    catch(const exception& e)
    {
        cerr << e.what();
    }
}

void SocialBots::add_echo_bot(Name src_channel, Name dest_channel)
{
    try
    {
        if(!is_channel_exists(src_channel))
            throw ChannelDoesntExist();
        if(!is_channel_exists(dest_channel))
            throw ChannelDoesntExist();
        if(src_channel == dest_channel)
            throw SameSrcDest();

        Channel* src = find_channel_by_name(src_channel);
        Channel* dest = find_channel_by_name(dest_channel);
        EchoBot* echo_bot = new EchoBot(src, dest);
        src->add_bot_to_channel(echo_bot);
        bots.push_back(echo_bot);
    }
    catch(const exception& e)
    {
        cerr << e.what();
    }
}

void SocialBots::add_logger_bot(Name filename)
{
    try
    {
        LoggerBot* logger_bot = new LoggerBot(filename);
        add_logger_bot_to_current_channels(logger_bot);
        bots.push_back(logger_bot);
    }
    catch(const exception& e)
    {
        cerr << e.what();
    }
}

void SocialBots::add_fred_bot(Name channel)
{
    try
    {
        if(!is_channel_exists(channel))
            throw ChannelAlreadyExist();

        Channel* src = find_channel_by_name(channel);
        FredBot* fred_bot = new FredBot(src);
        src->add_bot_to_channel(fred_bot);
        bots.push_back(fred_bot);
    }
    catch(const exception& e)
    {
        cerr << e.what();
    }
}

void SocialBots::add_librarian_bot(Name channel)
{
    try
    {
        if(!is_channel_exists(channel))
            throw ChannelAlreadyExist();

        Channel* src = find_channel_by_name(channel);
        LibrarianBot* librarian_bot = new LibrarianBot(src);
        src->add_bot_to_channel(librarian_bot);
        bots.push_back(librarian_bot);
    }
    catch(const exception& e)
    {
        cerr << e.what();
    }
}

void SocialBots::tell(Name channel, std::string message)
{
    try
    {
        if(!is_channel_exists(channel))
            throw ChannelAlreadyExist();

        Channel* src = find_channel_by_name(channel);
        src->send_message(message);
    }
    catch(const exception& e)
    {
        cerr << e.what();
    }
}

Channel* SocialBots::find_channel_by_name(Name name)
{
    for(int i = 0; i < channels.size(); i++)
        if(channels[i]->get_name() == name)
            return channels[i];

    return NULL;
}

void SocialBots::add_logger_bot_to_current_channels(LoggerBot* logger_bot)
{
    for(int i = 0; i < channels.size(); i++)
        channels[i]->add_bot_to_channel(logger_bot);
}

bool SocialBots::is_channel_exists(Name channel)
{
    for(int i = 0; i < channels.size(); i++)
        if(channels[i]->get_name() == channel)
            return true;

    return false;
}