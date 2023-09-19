#include "DELETE.hpp"

using namespace std;

DELETE::DELETE(UTRIP* utrip_, vector <string> commands_)
{
    utrip = utrip_;
    commands = commands_;
}

string DELETE::find_value(string kind)
{
    for(int i = 2; i < commands.size(); i++)
        if(commands[i] == kind)
            return commands[i + 1];
    throw ExceptionHandling(BAD_REQUEST_ERROR);
}

void DELETE::read_command()
{
    string command = commands[1];

    if(command == RESERVES_COMMAND)
    {
        try {
            int reservation_id = stoi(find_value(ID));
            utrip->cancel_reservation(reservation_id);
            cout << OK;
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == FILTERS_COMMAND)
    {
        try {
            utrip->delete_filters();
            cout << OK;
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else
        throw ExceptionHandling(NOT_FOUND_ERROR);
}