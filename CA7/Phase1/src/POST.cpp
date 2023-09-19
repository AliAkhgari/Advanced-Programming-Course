#include "POST.hpp"

using namespace std;

POST::POST(UTRIP* utrip_, vector <string> commands_)
{
    utrip = utrip_;
    commands = commands_;
}

void POST::read_command()
{
    string command = commands[1];

    if(command == SIGNUP_COMMAND)
    {
        string email, username, password;
        try {
            email = find_value(EMAIL);
            username = find_value(USERNAME);
            password = find_value(PASSWORD);
            utrip->sign_up(username, email, password);
            cout << OK;
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == LOGIN_COMMAND)
    {
        string email, password;
        try {
            email = find_value(EMAIL);
            password = find_value(PASSWORD);
            utrip->login(email, password);
            cout << OK;
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == LOGOUT_COMMAND)
    {
        try {
            utrip->logout();
            cout << OK;
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == WALLET_COMMAND)
    {
        double amount;
        try {
            amount = stod(find_value(AMOUNT));
            utrip->increase_balance(amount);
            cout << OK;
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == FILTERS_COMMAND)
    {
        string filter_kind = filter_type();
        if(filter_kind == "city")
        {
            string city = find_city_name();
            try {
                utrip->filter_city(city);
                cout << OK;
            } catch(const exception& e) {
                cout << e.what() << '\n';
            }
        }
        else if(filter_kind == "star")
        {
            int min_star, max_star;
            try {
                min_star = stoi(find_value(MIN_STAR));
                max_star = stoi(find_value(MAX_STAR));
                utrip->filter_star(min_star, max_star);
                cout << OK;
            } catch(const exception& e) {
                cout << e.what() << '\n';
            }
        }
        else if(filter_kind == "price")
        {
            int min_price, max_price;
            try {
                min_price = stoi(find_value(MIN_PRICE));
                max_price = stoi(find_value(MAX_PRICE));
                utrip->filter_price(min_price, max_price);
                cout << OK;
            } catch(const exception& e) {
                cout << e.what() << '\n';
            }
        }
        else if(filter_kind == "room")
        {
            string room_type;
            int quantity, check_in, check_out;
            try {
                room_type = find_value(ROOM_TYPE);
                quantity = stoi(find_value(QUANTITY));
                check_in = stoi(find_value(CHECK_IN));
                check_out = stoi(find_value(CHECK_OUT));
                utrip->filter_room(room_type, quantity, check_in, check_out);
                cout << OK;
            } catch(const exception& e) {
                cout << e.what() << '\n';
            }
        }
        else
            throw ExceptionHandling(BAD_REQUEST_ERROR); 
    }
    else if(command == RESERVES_COMMAND)
    {
        string hotel_id, room_type;
        int quantity, check_in, check_out;
        try {
            hotel_id = find_value(HOTEL_ID);
            room_type = find_value(ROOM_TYPE);
            quantity = stoi(find_value(QUANTITY));
            check_in = stoi(find_value(CHECK_IN));
            check_out = stoi(find_value(CHECK_OUT));
            utrip->reserve(hotel_id, room_type, quantity, check_in, check_out);
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == COMMENTS_COMMAND)
    {
        string hotel_id, comment;
        try {
            hotel_id = find_value(HOTEL_ID);
            comment = find_value(COMMENT);
            utrip->add_comment(hotel_id, comment);
            cout << OK;
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else if(command == RATINGS_COMMAND)
    {
        string hotel_id;
        double location, cleanliness, staff, facilities, value_for_money, overall_rating;
        try {
            hotel_id = find_value(HOTEL_ID);
            location = stod(find_value(LOCATION));
            cleanliness = stod(find_value(CLEANLINESS));
            staff = stod(find_value(STAFF));
            facilities = stod(find_value(FACILITIES));
            value_for_money = stod(find_value(VALUE_FOR_MONEY));
            overall_rating = stod(find_value(OVERALL_RATING));
            utrip->add_rating(hotel_id, location, cleanliness, staff, facilities, value_for_money, overall_rating);
            cout << OK;
        } catch(const exception& e) {
            cout << e.what() << '\n';
        }
    }
    else
        throw ExceptionHandling(NOT_FOUND_ERROR);
}

bool POST::is_have(string kind)
{
    for(int i = 2; i < commands.size(); i++)
        if(commands[i] == kind)
            return true;
    return false;
}

string POST::find_value(string kind)
{
    for(int i = 2; i < commands.size(); i++)
        if(commands[i] == kind)
            return commands[i + 1];
    throw ExceptionHandling(BAD_REQUEST_ERROR);
}

string POST::find_city_name()
{
    string city_name;
    for(int i = 2; i < commands.size(); i++)
    {
        if(commands[i] == "city")
        {
            for(int j = i + 1; j < commands.size(); j++)
            {
                city_name += commands[j];
                if(j != commands.size() - 1)
                    city_name += " ";
            }
            return city_name;
        }
    }  
    throw ExceptionHandling(BAD_REQUEST_ERROR);
}

string POST::filter_type()
{
    if(is_have("city"))
        return "city";
    else if(is_have("min_star"))
        return "star";
    else if(is_have("min_price"))
        return "price";
    else if(is_have("type"))
        return "room";
    else
        throw ExceptionHandling(BAD_REQUEST_ERROR);
}