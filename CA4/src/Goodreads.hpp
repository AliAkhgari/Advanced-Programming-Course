#ifndef GOODREADS_H
#define GOODREADS_H "GOODREADS_H"

#include "Author.hpp"
#include "User.hpp"
#include "Book.hpp"
#include "Review.hpp"
#include "FollowEdge.hpp"
#include "Functions.hpp"

class User;
class Author;
class Book;
class Review;
class FollowEdge;

class Goodreads
{
private:
    std::vector <User> users;
    std::vector <Author> authors;
    std::vector <Book> books;
    std::vector <Review> reviews;
    std::vector <FollowEdge> follow_edges;
public:
    Goodreads(std::vector <User> u, std::vector <Author> a, std::vector <Book> b,
              std::vector <Review> r, std::vector <FollowEdge> f);
    
    Author* find_author_by_id(int author_id);

    User* find_user_by_id(int user_id);

    Book* find_book_by_id(int book_id);

    std::vector <Book*> books_by_this_author(int author_id);

    std::vector <Review*> reviews_by_a_user(int user_id);

    std::vector <Review*> reviews_for_a_book(int book_id);

    FollowEdge* find_user_following(int user_id);

    void show_author_info(int author_id);

    void show_sorted_shelf(int user_id, std::string shelf_type, std::string genre);

    void print_books(std::vector <Book*> books_with_same_genre, std::vector <Book*> books_with_different_genre);

    float credit(int user_id);

    std::vector <float> books_rating_average(std::vector <Book*> all_books);

    void print_best_book_info(std::vector <Book*> all_books, std::vector <float> books_average);

    void find_best_book();

    std::vector <int> users_likes_number(std::vector <User*> all_users);

    void print_best_reviewer_info(User* best_reviewer, int max_element);

    void find_best_reviewer();

    std::vector <float> rating_of_books(User* user, std::vector <int> all_books);

    void recommend_first_approach(int user_id);
    
    void recommend_second_approach(int user_id);

    void all_user_followings(int user_id, std::vector <int> &all_followings);

    std::vector <int> best_three_books(int user_id);
};

#endif