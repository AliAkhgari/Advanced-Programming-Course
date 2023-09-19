#include "Goodreads.hpp"
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

Goodreads::Goodreads(vector <User> u, vector <Author> a, vector <Book> b, vector <Review> r, vector <FollowEdge> f)
{
    users = u;
    authors = a;
    books = b;
    reviews = r;
    follow_edges = f;
}

Author* Goodreads::find_author_by_id(int author_id)
{
    for(int i = 0 ; i < authors.size(); i++)
    {
        if(authors[i].get_id() == author_id)
            return &authors[i];
    }
    return NULL;
}

User* Goodreads::find_user_by_id(int user_id)
{
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i].get_id() == user_id)
            return &users[i];
    }
    return NULL;
}

Book* Goodreads::find_book_by_id(int book_id)
{
    for(int i = 0; i < books.size(); i++)
    {
        if(books[i].get_id() == book_id)
            return &books[i];
    }
    return NULL;
}

vector <Book*> Goodreads::books_by_this_author(int author_id)
{
    vector <Book*> books_of_author;
    for(int i = 0; i < books.size(); i++)
    {
        if(books[i].get_author_id() == author_id)
            books_of_author.push_back(&books[i]);
    }
    return books_of_author;
}

vector <Review*> Goodreads::reviews_by_a_user(int user_id)
{
    vector <Review*> user_reviews;
    for(int i = 0; i < reviews.size(); i++)
    {
        if(user_id == reviews[i].get_user_id())
            user_reviews.push_back(&reviews[i]);
    }
    return user_reviews;
}

vector <Review*> Goodreads::reviews_for_a_book(int book_id)
{
    vector <Review*> book_reviews;
    for(int i = 0; i < reviews.size(); i++)
    {
        if(book_id == stoi(reviews[i].get_book_id()))
            book_reviews.push_back(&reviews[i]);
    }
    return book_reviews;
}

FollowEdge* Goodreads::find_user_following(int user_id)
{
    for(int i = 0; i < follow_edges.size(); i++)
    {
        if(user_id == follow_edges[i].get_id())
            return &follow_edges[i];
    }
    return NULL;
}

void Goodreads::show_author_info(int author_id)
{
    Author* author = find_author_by_id(author_id);
    vector <string> author_genres = author->get_genres();
    sort(author_genres.begin(), author_genres.end());
    vector <Book*> author_books = books_by_this_author(author_id);
    sort(author_books.begin(), author_books.end(), compare_id);
    print_author_info(author, author_genres, author_books);
}

void Goodreads::print_books(vector <Book*> books_with_same_genre, vector <Book*> books_with_different_genre)
{
    for(int i = 0; i < books_with_same_genre.size(); i++)
    {
        Book* book = books_with_same_genre[i];
        Author* author = find_author_by_id(book->get_author_id());
        print_books_with_same_genre(books_with_same_genre, book, author);
        cout << STAR << endl;
    }
    for(int i = 0; i < books_with_different_genre.size(); i++)
    {
        Book* book = books_with_different_genre[i];
        Author* author = find_author_by_id(book->get_author_id());
        print_books_with_different_genre(books_with_different_genre, book, author);
        cout << STAR << endl;
    }
}

void Goodreads::show_sorted_shelf(int user_id, string shelf_type, string genre)
{
    User* user = find_user_by_id(user_id);
    vector <string> books_id;
    books_id = shelf_books(user, shelf_type);
    vector <Book*> books_with_same_genre;
    vector <Book*> books_with_different_genre;
    for(int i = 0; i < books_id.size(); i++)
    {
        Book* book = find_book_by_id(stoi(books_id[i])); 
        if(book->get_genre() == genre)
            books_with_same_genre.push_back(book);
        else
            books_with_different_genre.push_back(book);
    }
    sort(books_with_same_genre.begin(), books_with_same_genre.end(), compare_title);
    sort(books_with_different_genre.begin(), books_with_different_genre.end(), compare_title);
    print_books(books_with_same_genre, books_with_different_genre);
}

float Goodreads::credit(int user_id)
{
    float number_of_reviews = reviews.size();
    vector <Review*> user_reviews = reviews_by_a_user(user_id);
    float number_of_user_reviews = user_reviews.size();
    float number_of_likes = 0, number_of_user_reviews_likes = 0;
    for(int i = 0; i < user_reviews.size(); i++)
        number_of_user_reviews_likes += user_reviews[i]->get_number_of_likes();
    for(int i = 0; i < reviews.size(); i++)
        number_of_likes += reviews[i].get_number_of_likes();

    float user_credit = 0.5 * (division(number_of_user_reviews_likes, number_of_likes) + division(number_of_user_reviews, number_of_reviews));
    return user_credit;
}

vector <float> Goodreads::books_rating_average(vector <Book*> all_books)
{
    vector <float> books_average;
    for(int i = 0; i < all_books.size(); i++)
    {
        vector <Review*> book_reviews;
        book_reviews = reviews_for_a_book(all_books[i]->get_id());
        float sum = 0;
        for(int j = 0; j < book_reviews.size(); j++)
            sum += book_reviews[j]->get_rating();
        books_average.push_back(sum/book_reviews.size());
    }
    return books_average;
}

void Goodreads::print_best_book_info(vector <Book*> all_books, vector <float> books_average)
{
    int max_element_index = max_element_vector_index(books_average);
    float best_book_average_rating = books_average[max_element_index];
    Book* best_book = all_books[max_element_index];
    cout << ID << best_book->get_id() << endl << TITLE << best_book->get_title() 
    << endl << GENRE << best_book->get_genre() 
    << endl << AUTHOR << find_author_by_id(best_book->get_author_id())->get_name()
    << endl << AVERAGE_RATING << fixed << setprecision(2) << best_book_average_rating << endl;
}

void Goodreads::find_best_book()
{
    vector <Book*> all_books;
    for(int i = 0; i < books.size(); i++)
        all_books.push_back(&books[i]);
    vector <float> books_rate_average = books_rating_average(all_books);

    print_best_book_info(all_books, books_rate_average);
}

vector <int> Goodreads::users_likes_number(vector <User*> all_users)
{
    vector <int> users_likes;
    for(int i = 0; i < all_users.size(); i++)
    {
        vector <Review*> user_reviews;
        user_reviews = reviews_by_a_user(all_users[i]->get_id());
        int number_of_likes = 0;
        for(int j = 0; j < user_reviews.size(); j++)
        {
            number_of_likes += user_reviews[j]->get_number_of_likes();
        }
        users_likes.push_back(number_of_likes);
    }
    return users_likes;
}

void Goodreads::print_best_reviewer_info(User* best_reviewer, int max_element)
{
    cout << ID << best_reviewer->get_id() << endl << NAME << best_reviewer->get_name()
    << endl << PLACE_OF_BIRTH << best_reviewer->get_place_of_birth() << endl << MEMBER_SINCE <<
    best_reviewer->get_member_since() << endl << FAVORITE_GENRES;
    print_vector_elements(best_reviewer->get_favorite_genres());
    cout << endl << FAVORITE_AUTHORS;
    vector <Author*> favorite_authors;
    for(int i = 0; i < best_reviewer->get_favorite_authors().size(); i++)
    {
        Author* author = find_author_by_id(stoi(best_reviewer->get_favorite_authors()[i]));
        favorite_authors.push_back(author);
    }
    sort(favorite_authors.begin(), favorite_authors.end(), compare_author_title);
    for(int i = 0; i < favorite_authors.size(); i++)
    {
        cout << favorite_authors[i]->get_name();
        if(i != best_reviewer->get_favorite_authors().size() - 1)
            cout << COMMA;
    }
    cout << endl << NUMBER_OF_BOOKS_IN_READ_SHELF << best_reviewer->get_read().size()
    << endl << NUMBER_OF_BOOKS_IN_WANT_TO_READ_SHELF << best_reviewer->get_want_to_read().size()
    << endl << NUMBER_OF_BOOKS_IN_CURRENTLY_READING_SHELF << best_reviewer->get_currently_reading().size() 
    << endl << NUMBER_OF_LIKES <<  max_element  << endl;
}

void Goodreads::find_best_reviewer()
{
    vector <User*> all_users;
    for(int i = 0; i < users.size(); i++)
        all_users.push_back(&users[i]);
    vector <int> users_likes = users_likes_number(all_users);
    int max_element_index = max_element_vector_index(users_likes);
    int max_element = users_likes[max_element_index];
    User* best_reviewer = all_users[max_element_index];

    print_best_reviewer_info(best_reviewer, max_element);
}

vector <float> Goodreads::rating_of_books(User* user, vector <int> all_books)
{
    vector <float> books_rating;
    for(int i = 0; i < all_books.size(); i++)
    {
        Book* book = find_book_by_id(all_books[i]);
        vector <Review*> reviews_for_book = reviews_for_a_book(all_books[i]);
        float review_rating, user_credit, rating = 0;
        float number_of_reviews_of_book = reviews_for_book.size();
        for(int j = 0; j < reviews_for_book.size(); j++)
        {
            user_credit = credit(reviews_for_book[j]->get_user_id());
            review_rating = reviews_for_book[j]->get_rating();
            rating += review_rating * division(user_credit, number_of_reviews_of_book);
        }
        for(int j = 0; j < user->get_favorite_genres().size(); j++)
        {
            if(user->get_favorite_genres()[j] == book->get_genre())
            {
                rating += 5;
                break;
            }
        }
        books_rating.push_back(rating);
    }
    return books_rating;
}

void Goodreads::recommend_first_approach(int user_id)
{
    User* user = find_user_by_id(user_id);
    vector <int> all_books;
    vector <float> books_rating;
    vector <Review*> reviews_of_user = reviews_by_a_user(user_id);
    for(int i = 0; i < books.size(); i++)
        all_books.push_back(books[i].get_id());

    books_rating = rating_of_books(user, all_books);
    int max_element_index = max_element_vector_index(books_rating);

    Book* book = find_book_by_id(all_books[max_element_index]);
    Author* author = find_author_by_id(book->get_author_id());

    vector <Review*> reviews_of_book = reviews_for_a_book(book->get_id());
    sort(reviews_of_book.begin(), reviews_of_book.end(), compare_review);
    print_recommended_books_info(book, author, reviews_of_book);
}
void Goodreads::all_user_followings(int user_id, vector <int> &all_followings)
{
    FollowEdge* follow_edge = find_user_following(user_id);
    static vector <int> tmp;
    if(follow_edge->get_following().size() > 1)
    {
        if(tmp.size() != 0 && tmp[tmp.size() - 1] == follow_edge->get_id())
        {
            cout << tmp[tmp.size() - 1]<<endl;
            tmp.pop_back();
            if(member_number(tmp, follow_edge->get_id()) == 0 && tmp.size() != 0)
                tmp.pop_back();
        }
        else
        {
            for(int i = 0; i < follow_edge->get_following().size(); i++)
            {
                tmp.push_back(follow_edge->get_id());
            }
        }
    }
    if(follow_edge->get_following().size() > 1 && tmp.size() != 0)
        all_followings.push_back(stoi(follow_edge->get_following()[member_number(tmp, tmp[tmp.size() - 1]) - 1]));
    else
    {
        all_followings.push_back(stoi(follow_edge->get_following()[0]));
    }
    if(has_duplicate(all_followings) == false)
    {
        int last_following = all_followings[all_followings.size() - 1];
        return all_user_followings(last_following, all_followings);
    }
    else if(tmp.size() != 0)
    {
        all_followings.pop_back();
        int last_following = tmp[tmp.size() - 1];//0
        return all_user_followings(last_following, all_followings);
    }
    else
    {
        all_followings.pop_back();
        return;
    }    
}

vector <int> Goodreads::best_three_books(int user_id)
{
    User* user = find_user_by_id(user_id);
    vector <int> read_books;
    vector <float> book_rating;
    for(int i = 0; i < user->get_read().size(); i++)
        read_books.push_back(stoi(user->get_read()[i]));
    
    book_rating = rating_of_books(user, read_books);
    for(int i = 0; i < read_books.size(); i++)
    {
        if(book_rating[i] > 5)
            book_rating[i] -= 5;
    }
    sort_books_rating(read_books, book_rating);

    return best_three_of_vector(read_books);
}

void Goodreads::recommend_second_approach(int user_id)
{
    vector <int> all_followings;
    all_user_followings(user_id, all_followings);
    
    if(all_followings[all_followings.size() - 1] == user_id)
        all_followings.pop_back();
    vector <int> best_books;
    vector <int> best_3_books;
    for(int i = 0; i < all_followings.size(); i++)
    {
        best_3_books = best_three_books(all_followings[i]);
        for(int j = 0; j < best_3_books.size(); j++)
            best_books.push_back(best_3_books[j]);
    }
    vector <float> repeat = number_of_vector_members(best_books);
    int index = max_element_vector_index(repeat);
    vector <int> indexes = max_indexes(repeat, index);
    int book_id = best_books[indexes[0]];

    for(int i = 0; i < indexes.size(); i++)
    {
        if(best_books[indexes[i]] < book_id)
        {
            book_id = best_books[indexes[i]];
        }
    }
    Book* book = find_book_by_id(book_id);
    Author* author = find_author_by_id(book->get_author_id());
    vector<Review*> review = reviews_for_a_book(book->get_id());
    print_recommended_books_info(book, author, review);
}