#include "Review.hpp"

using namespace std;

vector <Review> Review::review_info(vector <string> data)
{
    vector <Review> reviews;
    int counter = 0;
    for(int i = 0; i < data.size(); i++)
    {
        if(i % 6 == 0)
        {
            reviews.push_back(Review());
            reviews[counter].id = stoi(data[i]);
        }
        if(i % 6 == 1)
            reviews[counter].book_id = data[i];
        if(i % 6 == 2)
            reviews[counter].user_id = stoi(data[i]);
        if(i % 6 == 3)
            reviews[counter].rating = stoi(data[i]);
        if(i % 6 == 4)
            reviews[counter].date = data[i];
        if(i % 6 == 5)
        {
            reviews[counter].number_of_likes = stoi(data[i]);
            counter++;
        }
    }
    return reviews;
}

Id Review::get_id () { return id; }

string Review::get_book_id () { return book_id; }

Id Review::get_user_id () { return user_id; }

int Review::get_rating () { return rating; }

Date Review::get_date () { return date; }

int Review::get_number_of_likes () { return number_of_likes; }