#include "Functions.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ostream>
#include <sstream>
#include <iomanip>

using namespace std;

vector <string> file_seperated_data(string file_content, char token)
{
    stringstream file_data(file_content);
    string line;
    vector <string> data;
    string cell;
    while(getline(file_data, line, '\n'))
    {
        stringstream line_data(line);
        while(getline(line_data, cell, token))
        {
            data.push_back(cell);
        }
    }
    return data;
}

vector <string> follow_edge_seperated_data(string content)
{
    stringstream file_data(content);
    string line;
    vector <string> data;
    string cell;
    while(getline(file_data, line, '\n'))
    {
        int counter = 0;
        stringstream line_data(line);
        while(getline(line_data, cell, ','))
        {
            if(counter >= 2)
                break;
            data.push_back(cell);
            counter++;
        }
    }
    return data;
}

string file_content(string file_name)
{
    ifstream input_file(file_name);
    input_file.ignore(numeric_limits <streamsize>::max(),'\n');
    stringstream file_content;
    file_content << input_file.rdbuf();
    return file_content.str();
}

vector <string> file_data(string file_path)
{
    string file_info = file_content(file_path);
    vector <string> data;
    if(file_path == "Assets/follow_edges.csv")
    {
        data = follow_edge_seperated_data(file_info);
    }
    else
        data = file_seperated_data(file_info, ',');
    return data;
}

void print_author_info(Author* author, vector <string> author_genres, vector <Book*> books_of_author)
{
    cout << ID << author->get_id() << endl << NAME << author->get_name() << endl   
    << YEAR_OF_BIRTH << author->get_year_of_birth() << endl
    << PLACE_OF_BIRTH << author->get_place_of_birth() << endl
    << MEMBER_SINCE << author->get_member_since() << endl << GENRES;

    for(int i = 0; i < author_genres.size(); i++)
    {
        cout << author_genres[i];
        if(i != author_genres.size() - 1)
            cout << COMMA;
    }
    cout << endl << "Books:" << endl;
    for(int i = 0; i < books_of_author.size(); i++)
        cout << ID << books_of_author[i]->get_id() << " " << TITLE << books_of_author[i]->get_title() << endl;
}

int max_element_vector_index(vector <int> input)
{
    int max_element_index = 0;
    float max_element = input[0];
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] > max_element)
        {
            max_element = input[i];
            max_element_index = i;
        }
    }
    return max_element_index;
}

bool compare_review(Review* review1, Review* review2)
{
    return review1->get_id() < review2->get_id();
}

bool compare_id(Book* book1, Book* book2)
{
    return book1->get_id() < book2->get_id();
}

bool compare_title(Book* book1, Book* book2)
{
    if(book1->get_title() == book2->get_title())
        return book1->get_id() < book2->get_id();
    return book1->get_title() < book2->get_title();
}

bool compare_author_title(Author* author1, Author* author2)
{
    if(author1->get_name() == author2->get_name())
        return author1->get_id() < author2->get_id();
    return author1->get_name() < author2->get_name();
}

Book* best_book(vector <Book*> all_books, vector <float> books_average)
{
    int max_element_index = max_element_vector_index(books_average);
    float best_book_average_rating = books_average[max_element_index];
    return all_books[max_element_index];
}

bool has_duplicate(vector <int> input)
{
    for(int i = 0; i < input.size(); i++)
    {
        for(int j = i + 1; j < input.size(); j++)
        {
            if(input[i] == input[j])
                return true;
        }
    }
    return false;
}

int member_number(vector <int> input, int number)
{
    int counter = 0;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] == number)
            counter++;
    }
    return counter;
}

vector <string> shelf_books(User* user, string shelf_type)
{
    vector <string> books_id;
    if(shelf_type == WANT_TO_READ)
        books_id = user->get_want_to_read();
    if(shelf_type == READ)
        books_id = user->get_read();
    if(shelf_type == CURRENTLY_READING)
        books_id = user->get_currently_reading();
    return books_id;
}

void print_books_with_same_genre(vector <Book*> books_with_same_genre, Book* book, Author* author)
{
    cout << ID << book->get_id() << endl << TITLE << book->get_title() 
    << endl << GENRE << book->get_genre() << endl << AUTHOR << author->get_name() << endl;
}

void print_books_with_different_genre(vector <Book*> books_with_different_genre, Book* book, Author* author)
{
    cout << ID << book->get_id() << endl << TITLE << book->get_title() << endl << 
    GENRE << book->get_genre() << endl << AUTHOR << author->get_name() << endl;
}

float division(float first, float second)
{
    if(second == 0)
        return 0;
    else
        return first/second;  
}

void print_vector_elements(vector <string> input)
{
    sort(input.begin(), input.end());
    for(int i = 0; i < input.size(); i++)
    {
        cout << input[i];
        if(i != input.size() - 1)
            cout << COMMA;
    }
}

int max_element_vector_index(vector <float> input)
{
    int max_element_index = 0;
    float max_element = input[0];
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] > max_element)
        {
            max_element = input[i];
            max_element_index = i;
        }
    }
    return max_element_index;
}

void print_recommended_books_info(Book* book, Author* author, vector <Review*> reviews_of_book)
{
    cout << ID << book->get_id() << endl << TITLE << book->get_title() << endl << GENRE << book->get_genre() << endl <<
    AUTHOR << author->get_name() << endl << REVIEWS <<endl;
    sort(reviews_of_book.begin(), reviews_of_book.end(), compare_review);
    for(int i = 0 ; i < reviews_of_book.size(); i++)
    {
        cout << ID << reviews_of_book[i]->get_id() << " Rating: " << reviews_of_book[i]->get_rating() << " Likes: " <<
        reviews_of_book[i]->get_number_of_likes() << " Date: " << reviews_of_book[i]->get_date() << endl; 
    }
}

void sort_books_rating(vector <int> &read_books, vector <float> &book_rating)
{
    for(int i = 0; i < book_rating.size(); i++)
    {
        for(int j = i + 1 ; j < book_rating.size(); j++)
        {
            if(book_rating[j] < book_rating[i])
            {
                swap(book_rating[i], book_rating[j]);
                swap(read_books[i], read_books[j]);
            }
        }
    }
}

vector <int> best_three_of_vector(vector <int> input)
{
    vector <int> best_three;
    int last_index = input.size() - 1;
    for(int i = last_index; i >= 0; i--)
    {
        if(best_three.size() >= 3)
            break;
        best_three.push_back(input[i]);
    }
    return best_three;
}

vector <float> number_of_vector_members(vector <int> input)
{
    vector <float> repeat(input.size());
    for(int i = 0; i < input.size(); i++)
    {
        for(int j = i; j < input.size(); j++)
        {
            if(input[i] == input[j])
                repeat[i]++;
        }
    }
    return repeat;
}

vector <int> max_indexes(vector <float> input, int index)
{
    vector <int> indexes;
    for(int i = 0; i < input.size(); i++)
    {
        if(input[i] == input[index])
            indexes.push_back(i);
    }
    return indexes;
}

string deleted_first_char(string input)
{
    string output;
    for(int i = 1; i < input.length(); i++)
        output += input[i];
    return output;
}

void get_command(string command, Goodreads goodreads)
{
    if(command == SHOW_AUTHOR_INFO)
    {
        int author_id;
        cin >> author_id;
        goodreads.show_author_info(author_id);
    }

    if(command == SHOW_SORTED_SHELF)
    {
        int user_id;
        string shelf_type, genre;
        cin >> user_id >> shelf_type;
        getline(cin, genre);
        genre = deleted_first_char(genre);
        goodreads.show_sorted_shelf(user_id, shelf_type, genre);
    }

    if(command == CREDIT)
    {
        int user_id;
        cin >> user_id;
        float user_credit = goodreads.credit(user_id);
        cout << fixed << setprecision(6) << user_credit << endl;
    }

    if(command == BEST_BOOK)
        goodreads.find_best_book();
    
    if(command == BEST_REVIEWER)
        goodreads.find_best_reviewer();
    
    if(command == RECOMMEND_FIRST_APPROACH)
    {
        Id user_id;
        cin >> user_id;
        goodreads.recommend_first_approach(user_id);
    }

    if(command == RECOMMEND_SECOND_APPROACH)
    {
        Id user_id;
        cin >> user_id;
        goodreads.recommend_second_approach(user_id);
    }
}

Goodreads push_file_datas(string users_file_path, string authors_file_path, 
                            string books_file_path, string reviews_file_path, string follow_edges_file_path)
{
    User user;
    Author author;
    Book book;
    Review review;
    FollowEdge follow_edge;
    
    vector <User> users = user.user_info(file_data(users_file_path));
    vector <Author> authors = author.author_info(file_data(authors_file_path));
    vector <Book> books = book.book_info(file_data(books_file_path));
    vector <Review> reviews = review.review_info(file_data(reviews_file_path));
    vector <FollowEdge> follow_edges = follow_edge.follow_edge_info(file_data(follow_edges_file_path));

    Goodreads goodreads(users, authors, books, reviews, follow_edges);

    return goodreads;
}
