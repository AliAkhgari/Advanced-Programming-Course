#include "SocialBots.hpp"

#define ADD_CHANNEL_COMMAND "add_channel"
#define ADD_BOT_COMMAND "add_bot"
#define ECHO "echo"
#define FREIND "fred"
#define LOGGER "logger"
#define LIBRARIAN "librarian"
#define TELL_COMMAND "tell"

using namespace std;

typedef string Name;

void get_command(SocialBots social_bots);

int main()
{
    SocialBots social_bots;
    
    get_command(social_bots);

    return 0;
}

void get_command(SocialBots social_bots)
{
    string command;//__________****___________
    while(cin >> command)
    {
        if(command == ADD_CHANNEL_COMMAND)
        {
            Name channel;
            cin >> channel;
            social_bots.add_channel(channel);
        }
        if(command == ADD_BOT_COMMAND)
        {
            string bot_type;
            cin >> bot_type;
            if(bot_type == ECHO)
            {
                Name src_channel, dest_channel;
                cin >> src_channel >> dest_channel;
                social_bots.add_echo_bot(src_channel, dest_channel);
            }
            if(bot_type == LOGGER)
            {
                Name file;
                cin >> file;
                social_bots.add_logger_bot(file);
            }
            if(bot_type == FREIND)
            {
                Name channel;
                cin >> channel;
                social_bots.add_fred_bot(channel);
            }
            if(bot_type == LIBRARIAN)
            {
                Name channel;
                cin >> channel;
                social_bots.add_librarian_bot(channel);
            }
        }
        if(command == TELL_COMMAND)
        {
            Name channel;
            string message;
            cin >> channel;
            getline(cin, message);
            message = message.substr(1, message.size() - 1);
            social_bots.tell(channel, message);
        }
    }
}