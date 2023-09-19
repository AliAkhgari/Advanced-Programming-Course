#include "GET.hpp"

using namespace std;

GET::GET(UTRIP* utrip_, vector <string> commands_)
{
    utrip = utrip_;
    commands = commands_;
}

bool GET::is_have(string kind)
{
    for(int i = 2; i < commands.size(); i++)
        if(commands[i] == kind)
            return true;
    return false;
}

string GET::find_value(string kind)
{
    for(int i = 2; i < commands.size(); i++)
        if(commands[i] == kind)
            return commands[i + 1];
    throw ExceptionHandling(BAD_REQUEST_ERROR);
}

void GET::read_command()
{
    string command = commands[1];
    if(command == WALLET_COMMAND)
    {
        int count = stoi(find_value(COUNT));
        try {
            utrip->get_turnover(count);
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }   
    }
    else if(command == HOTELS_COMMAND && !is_have(QUESTION_MARK))
    {
        try {
            utrip->show_hotels_info();
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == HOTELS_COMMAND && is_have(QUESTION_MARK))
    {
        string hotel_id;
        try {
            hotel_id = find_value(ID);
            utrip->show_hotel_info(hotel_id);
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == RESERVES_COMMAND)
    {
        try {
            utrip->get_user_reserves();
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == COMMENTS_COMMAND)
    {
        string hotel_id;
        hotel_id = find_value(HOTEL_ID);
        try {
            utrip->show_comments(hotel_id);
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == RATINGS_COMMAND)
    {
        string hotel_id;
        hotel_id = find_value(HOTEL_ID);
        try {
            utrip->show_rating(hotel_id);
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == MANUAL_WEIGHTS_COMMAND)
    {
        try {
            utrip->show_manual_weights();
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == ESTIMATED_WEIGHTS_COMMAND)
    {
        try {
            utrip->show_estimated_weights();
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else
        throw ExceptionHandling(NOT_FOUND_ERROR);
}