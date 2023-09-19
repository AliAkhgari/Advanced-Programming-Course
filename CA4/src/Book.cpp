#include "Book.hpp"
// #include <vector>
#include <string>
using namespace std;

typedef std::string Name;
typedef std::string Genre;
typedef std::string Date;
typedef int Id;
typedef std::vector <std::string> Genres;
typedef std::vector <std::string> BooksId;
typedef std::vector <std::string> AuthorsId;

vector <Book> Book::book_info(vector <string> data)
{
    vector <Book> books;
    int counter = 0;
    for(int i = 0; i < data.size(); i++)
    {
        if(i % 4 == 0)
        {
            books.push_back(Book());
            books[counter].id = stoi(data[i]);
        }
        if(i % 4 == 1)
            books[counter].title = data[i];
        if(i % 4 == 2)
            books[counter].author_id = stoi(data[i]);
        if(i % 4 == 3)
        {
            books[counter].genre = data[i];
            counter++;
        }
    }
    return books;
}

Id Book::get_id () { return id; }
Name Book::get_title () { return title; }
Id Book::get_author_id () { return author_id; }
Genre Book::get_genre () { return genre; }