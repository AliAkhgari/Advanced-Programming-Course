#ifndef AUTHOR_H
#define AUTHOR_H "AUTHOR_H"
#include "Functions.hpp"
#include <string>

typedef std::string Name;
typedef std::string Genre;
typedef std::string Date;
typedef int Id;
typedef std::vector <std::string> Genres;
typedef std::vector <std::string> BooksId;
typedef std::vector <std::string> AuthorsId;

class Author
{
private:
    Id id;
    Name name;
    std::string gender;
    Date member_since;
    int year_of_birth;
    std::string place_of_birth; 
    Genres genres;
public:
    std::vector <Author> author_info(std::vector <std::string> data);
    Id get_id ();
    Name get_name ();
    std::string get_gender ();
    Date get_member_since ();
    int get_year_of_birth ();
    std::string get_place_of_birth ();
    Genres get_genres ();
};


#endif