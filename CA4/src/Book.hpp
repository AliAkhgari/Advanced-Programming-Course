#ifndef BOOK_H
#define BOOK_H "BOOK_H"
#include "Functions.hpp"
#include "Author.hpp"
#include <vector>

typedef std::string Name;
typedef std::string Genre;
typedef std::string Date;
typedef int Id;
typedef std::vector <std::string> Genres;
typedef std::vector <std::string> BooksId;
typedef std::vector <std::string> AuthorsId;

class Book
{
private:
    Id id;
    Name title;
    Id author_id;
    Genre genre;
public:
    std::vector <Book> book_info(std::vector <std::string> data);
    Id get_id ();
    Name get_title ();
    Id get_author_id ();
    Genre get_genre ();
};


#endif