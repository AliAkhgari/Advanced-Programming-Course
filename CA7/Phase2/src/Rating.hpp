#ifndef __RATING_H__
#define __RATING_H__ "__RATING_H__"

#include <string>
#include <vector>

typedef double Score;

class Rating
{
private:
    std::string user_name;
    Score location;
    Score cleanliness;
    Score staff;
    Score facilities;
    Score value_for_money;
    Score overall_rating;

public:
    Rating(std::string user_name_, Score location_, Score cleanliness_,
               Score staff_, Score facilities_, Score value_for_money_, Score overall_rating_);

    std::string get_user_name () { return user_name; }

    double get_overall_rating () { return overall_rating; }

    std::vector <Score> get_rating()
    {
        std::vector <Score> scores = { location, cleanliness, staff, facilities, value_for_money};
        return scores;
    }
};

#endif