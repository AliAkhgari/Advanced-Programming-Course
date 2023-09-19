#ifndef USER_H
#define USER_H "USER_H"
#include <string>
#include <vector>
#include "Functions.hpp"

typedef std::string Name;
typedef std::string Genre;
typedef std::string Date;
typedef int Id;
typedef std::vector <std::string> Genres;
typedef std::vector <std::string> BooksId;
typedef std::vector <std::string> AuthorsId;


class User
{
private:
    Id id;
    Name name;
    std::string place_of_birth;
    Date member_since;
    AuthorsId favorite_authors;
    Genres favorite_genres;
    BooksId want_to_read;
    BooksId currently_reading;
    BooksId read;
public:
    std::vector <User> user_info(std::vector <std::string> data);
    Id get_id ();
    Name get_name ();
    std::string get_place_of_birth ();
    Date get_member_since ();
    AuthorsId get_favorite_authors ();
    Genres get_favorite_genres ();
    BooksId get_want_to_read ();
    BooksId get_currently_reading ();
    BooksId get_read ();
};

#endif