#include "Channel.hpp"

using namespace std;

void Channel::send_message(string message)
{
    messages.push_back(message);
    notify_joined_bot(message);
}

void Channel::add_bot_to_channel(Bot* bot)
{
    joined_bot.push_back(bot);
}

void Channel::notify_joined_bot(string message)
{
    for(int i = 0; i < joined_bot.size(); i++)
        joined_bot[i]->notify(message);
}