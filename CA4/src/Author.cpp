#include "Author.hpp"
#include <vector>

using namespace std;

vector <Author> Author::author_info(vector <string> data)
{
    vector <Author> authors;
    int counter = 0;
    for(int i = 0; i < data.size(); i++)
    {
        if(i % 7 == 0)
        {
            authors.push_back(Author());
            authors[counter].id = stoi(data[i]);
        }
        if(i % 7 == 1)
            authors[counter].name = data[i];
        if(i % 7 == 2)
            authors[counter].gender = data[i];
        if(i % 7 == 3)
            authors[counter].member_since = data[i];
        if(i % 7 == 4)
            authors[counter].year_of_birth = stoi(data[i]);
        if(i % 7 == 5)
            authors[counter].place_of_birth = data[i];
        if(i % 7 == 6)
        {
            authors[counter].genres = file_seperated_data(data[i], '$');
            counter++;
        }
    }
    return authors;
}

Id Author::get_id () { return id; }
Name Author::get_name () { return name; }
string Author::get_gender () { return gender; }
Date Author::get_member_since () { return member_since; }
int Author::get_year_of_birth () { return year_of_birth; }
string Author::get_place_of_birth () { return place_of_birth; }
Genres Author::get_genres () { return genres; }