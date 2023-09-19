#ifndef REVIEW_H
#define REVIEW_H "REVIEW_H"

#include "Functions.hpp"
#include <string>
#include <vector>

typedef std::string Name;
typedef std::string Genre;
typedef std::string Date;
typedef int Id;
typedef std::vector <std::string> Genres;
typedef std::vector <std::string> BooksId;
typedef std::vector <std::string> AuthorsId;

class Review
{
private:
    Id id;
    std::string book_id;
    Id user_id;
    int rating;
    Date date;
    int number_of_likes;
public:
    std::vector <Review> review_info(std::vector <std::string> data);
    Id get_id ();
    std::string get_book_id ();
    Id get_user_id ();
    int get_rating ();
    Date get_date ();
    int get_number_of_likes ();
};

#endif