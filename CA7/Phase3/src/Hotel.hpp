#ifndef __HOTEL_H__
#define __HOTEL_H__ "__HOTEL_H__"

#include <string>
#include <vector>
#include <iostream>
#include <iomanip> 
#include "Room.hpp"
#include "ExceptionHandling.hpp"
#include "Rating.hpp"

#define STANDARD_ROOM "standard"
#define DELUXE_ROOM "deluxe"
#define LUXURY_ROOM "luxury"
#define PREMIUM_ROOM "premium"
#define RATINGS_COMMAND "ratings"
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY_TYPE "value for money"
#define OVERALL_RATING_TYPE "overall rating"
#define BAD_REQUEST_ERROR "Bad Request"
#define NO_RATING_ERROR "No Rating"

#define SEPERATOR " "
#define LOCATION_PRINT "location: "
#define CLEANLINESS_PRINT "\ncleanliness: "
#define STAFF_PRINT "\nstaff: "
#define FACILITIES_PRINT "\nfacilities: "
#define VALUE_FOR_MONEY_PRINT "\nvalue_for_money: "
#define OVERALL_RATING_PRINT "\noverall_rating: "

#define STAR_PRINT "\nstar: "
#define OVERVIEW_PRINT "\noverview: "
#define AMENITIES_PRINT "\namenities: "
#define CITY_PRINT "\ncity: "
#define LATITUDE_PRINT "\nlatitude: "
#define LONGITUDE_PRINT "\nlongitude: "
#define ROOMS_NUMBER_PRINT "\n#rooms: "
#define ROOMS_PRICE_PRINT "\nprice: "

#define STANDARD_ROOM_SIGN "s"
#define DELUXE_ROOM_SIGN "d"
#define LUXURY_ROOM_SIGN "l"
#define PREMIUM_ROOM_SIGN "p"

typedef int Number;
typedef int Price;
typedef double Score;
typedef std::string Name;
typedef std::string Info;
typedef std::vector <Room*> Rooms;

double vector_average(std::vector <std::pair <std::string, double> > input);
double price_average(double x, double y, double z, double t);

struct UserComment
{
    Name user_name;
    std::string comment;
    UserComment(Name user_name_, std::string comment_)
    {
        user_name = user_name_;
        comment = comment_;
    }
};

struct Ratings
{
    Score location;
    Score cleanliness;
    Score staff;
    Score facilities;
    Score value_for_money;
    Score overall_rating;
    Ratings() {}
    Ratings(Score location_, Score cleanliness_, Score staff_, 
            Score facilities_, Score value_for_money_, Score overall_rating_)
    {
        location = location_;
        cleanliness = cleanliness_;
        staff = staff_;
        facilities = facilities_;
        value_for_money = value_for_money_;
        overall_rating = overall_rating_;
    }
};

struct RoomsInfo
{
    Number num_of_standard_rooms;
    Number num_of_deluxe_rooms;
    Number num_of_luxury_rooms;
    Number num_of_premium_rooms;
    Price standard_room_price;
    Price deluxe_room_price;
    Price luxury_room_price;
    Price premium_room_price;
    Rooms standard_rooms;
    Rooms deluxe_rooms;
    Rooms luxury_rooms;
    Rooms premium_rooms;
    RoomsInfo() {}
    RoomsInfo(Number num_of_standard_rooms_, Number num_of_deluxe_rooms_, Number num_of_luxury_rooms_,
              Number num_of_premium_rooms_, Price standard_room_price_, Price deluxe_room_price_,
              Price luxury_room_price_, Price premium_room_price_)
    {
        num_of_standard_rooms = num_of_standard_rooms_;
        num_of_deluxe_rooms = num_of_deluxe_rooms_;
        num_of_luxury_rooms = num_of_luxury_rooms_;
        num_of_premium_rooms = num_of_premium_rooms_;
        standard_room_price = standard_room_price_;
        deluxe_room_price = deluxe_room_price_;
        luxury_room_price = luxury_room_price_;
        premium_room_price = premium_room_price_;
    }
};

class Hotel
{
private:
    std::string unique_id;
    Name name;
    int star_rating;
    Info overview;
    Info property_amenities;
    Name city;
    double latitude;
    double longitude;
    std::string imgage_url;
    RoomsInfo rooms_information;
    std::vector <UserComment> comments;
    Ratings average_ratings;
    std::vector <Rating> users_rating;
    double average_price;
    int total_num_of_rooms;

public:
    Hotel(std::vector <std::string> hotel_info);

    ~Hotel();

    Name get_city () { return city; }

    std::string get_id () { return unique_id; }

    std::string get_name () { return name; }

    int get_star () { return star_rating; }

    double get_average_price () { return average_price; }

    int get_total_num_of_rooms () { return total_num_of_rooms; }

    int get_standard_room_price () { return rooms_information.standard_room_price; }

    int get_deluxe_room_price () { return rooms_information.deluxe_room_price; }

    int get_luxury_room_price () { return rooms_information.luxury_room_price; }

    int get_premium_room_price () { return rooms_information.premium_room_price; }

    double get_overall_rating () { return average_ratings.overall_rating; }

    Ratings get_ratings () { return average_ratings; }

    Rooms find_rooms_by_kind(std::string room_kind);

    int room_price(std::string room_kind);

    void print(std::string mode);

    void add_comment(Name user_name, std::string comment);

    void show_comments();

    void set_rating(Score location, Score cleanliness, Score staff,
                    Score facilities, Score value_for_money, Score overall_rating);

    void add_rating(Name user_name, Score location, Score cleanliness, Score staff,
                Score facilities, Score value_for_money, Score overall_rating);

    void show_rating();

    bool has_first(Name user_name);

    int first_index(Name user_name);

    double user_overall_rating(std::string name, std::vector <double> manual_weights);

    double personal_overall_rating(std::string name, std::vector <double> weights);

    std::string get_image_url () { return imgage_url; }

    std::string get_overview () { return overview; }

    std::string get_property () { return property_amenities; }

    RoomsInfo get_rooms_info () { return rooms_information; }
};


#endif