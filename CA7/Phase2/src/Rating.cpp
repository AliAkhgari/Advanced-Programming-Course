#include "Rating.hpp"

using namespace std;

Rating::Rating(string user_name_, Score location_, Score cleanliness_,
            Score staff_, Score facilities_, Score value_for_money_, Score overall_rating_)
{
    user_name = user_name_;
    location = location_;
    cleanliness = cleanliness_;
    staff = staff_;
    facilities = facilities_;
    value_for_money = value_for_money_;
    overall_rating = overall_rating_;
}