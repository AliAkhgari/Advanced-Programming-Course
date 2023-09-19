#ifndef __LIBRARIAN_BOT_H__
#define __LIBRARIAN_BOT_H__ "__LIBRARIAN_BOT_H__"

#include "Bot.hpp"
#include "Channel.hpp"
#include <string>

typedef std::string Name;

class LibrarianBot : public Bot
{
private:
    Channel* channel;
    int times = 0;

public:
    LibrarianBot(Channel* channel_)
    {
        channel = channel_;
    }

    virtual void notify (std::string message)
    {
        times++;
        if(times % 5 == 0)
            channel->send_message("Quiet!");
    }

};



#endif