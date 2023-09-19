#ifndef FUNCTIONS_H
#define FUNCTIONS_H "FUNCTIONS_H"

#include <vector>
#include <string>
#include "User.hpp"
#include "Author.hpp"
#include "Book.hpp"
#include "Review.hpp"
#include "Goodreads.hpp"
#include "FollowEdge.hpp"

#define ID "id: "
#define NAME "Name: "
#define TITLE "Title: "
#define AUTHOR "Author: "
#define YEAR_OF_BIRTH "Year of Birth: "
#define PLACE_OF_BIRTH "Place of Birth: "
#define MEMBER_SINCE "Member Since: "
#define FAVORITE_GENRES "Favorite Genres: "
#define FAVORITE_AUTHORS "Favorite Authors: "
#define GENRES "Genres: "
#define GENRE "Genre: "
#define WANT_TO_READ "want_to_read"
#define CURRENTLY_READING "currently_reading"
#define READ "read"
#define AVERAGE_RATING "Average Rating: "
#define STAR "***"
#define NUMBER_OF_BOOKS_IN_READ_SHELF "Number of Books in Read Shelf: "
#define NUMBER_OF_BOOKS_IN_WANT_TO_READ_SHELF "Number of Books in Want to Read Shelf: "
#define NUMBER_OF_BOOKS_IN_CURRENTLY_READING_SHELF "Number of Books in Currently Reading Shelf: "
#define NUMBER_OF_LIKES "Number of Likes: "
#define COMMA ", "
#define SHOW_AUTHOR_INFO "show_author_info"
#define SHOW_SORTED_SHELF "show_sorted_shelf"
#define CREDIT "credit"
#define BEST_BOOK "best_book"
#define BEST_REVIEWER "best_reviewer"
#define RECOMMEND_FIRST_APPROACH "recommend_first_approach"
#define RECOMMEND_SECOND_APPROACH "recommend_second_approach"
#define REVIEWS "Reviews:"

typedef std::string Name;
typedef std::string Genre;
typedef std::string Date;
typedef int Id;
typedef std::vector <std::string> Genres;
typedef std::vector <std::string> BooksId;
typedef std::vector <std::string> AuthorsId;

class Goodreads;
class User;
class Author;
class Book;
class Review;
class FollowEdge;


std::vector <std::string> file_seperated_data(std::string file_content, char token);

std::string file_content(std::string file_name);

std::vector <std::string> file_data(std::string file_path);

void print_author_info(Author* author, std::vector <std::string> author_genres, std::vector <Book*> books_of_author);

int max_element_vector_index(std::vector <int> input);

bool compare_review(Review* review1, Review* review2);

bool compare_id(Book* book1, Book* book2);

bool compare_title(Book* book1, Book* book2);

bool compare_author_title(Author* author1, Author* author2);

std::vector <std::string> shelf_books(User* user, std::string shelf_type);

float division(float first, float second);

std::string deleted_first_char(std::string input);

std::vector <int> max_indexes(std::vector <float> input, int index);

std::vector <int> best_three_of_vector(std::vector <int> input);

void print_vector_elements(std::vector <std::string> input);

void print_books_with_same_genre(std::vector <Book*> books_with_same_genre, Book* book, Author* author);

void print_books_with_different_genre(std::vector <Book*> books_with_different_genre, Book* book, Author* author);

bool has_duplicate(std::vector <int> input);

int max_element_vector_index(std::vector <float> input);

Book* best_book(std::vector <Book*> all_books, std::vector <float> books_average);

std::vector <float> number_of_vector_members(std::vector <int> input);

void sort_books_rating(std::vector <int> &read_books, std::vector <float> &book_rating);

int member_number(std::vector <int> input, int number);

void print_recommended_books_info(Book* book, Author* author, std::vector <Review*> reviews_of_book);

void get_command(std::string command, Goodreads goodreads);

Goodreads push_file_datas(std::string users_file_path, std::string authors_file_path, 
        std::string books_file_path, std::string reviews_file_path, std::string follow_edges_file_path);


#endif