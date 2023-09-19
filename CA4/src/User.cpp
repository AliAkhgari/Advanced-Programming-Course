#include "User.hpp"
#include <vector>

using namespace std;

vector <User> User::user_info(vector <string> data)
{
    vector <User> users;
    int counter = 0;
    for(int i = 0; i < data.size(); i++)
    {
        if(i % 9 == 0)
        {
            users.push_back(User());
            users[counter].id = stoi(data[i]);
        }
        if(i % 9 == 1)
            users[counter].name = data[i];
        if(i % 9 == 2)
            users[counter].place_of_birth = data[i];
        if(i % 9 == 3)
            users[counter].member_since = data[i];
        if(i % 9 == 4)
            users[counter].favorite_authors = file_seperated_data(data[i], '$');
        if(i % 9 == 5)
            users[counter].favorite_genres = file_seperated_data(data[i], '$');
        if(i % 9 == 6)
            users[counter].want_to_read = file_seperated_data(data[i], '$');
        if(i % 9 == 7)
            users[counter].currently_reading = file_seperated_data(data[i], '$');
        if(i % 9 == 8)
        {
            users[counter].read = file_seperated_data(data[i], '$');
            counter++;
        }
    }
    return users;
}

Id User::get_id () { return id; }

Name User::get_name () { return name; }

string User::get_place_of_birth () { return place_of_birth; }

Date User::get_member_since () { return member_since; }

AuthorsId User::get_favorite_authors () { return favorite_authors; }

Genres User::get_favorite_genres () { return favorite_genres; }

BooksId User::get_want_to_read () { return want_to_read; }

BooksId User::get_currently_reading () { return currently_reading; }

BooksId User::get_read () { return read; }