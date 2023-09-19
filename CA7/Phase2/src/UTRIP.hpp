#ifndef __UTRIP_H__
#define __UTRIP_H__ "__UTRIP_H__"

#include <string>
#include <vector>
#include <algorithm>
#include "Hotel.hpp"
#include "Room.hpp"
#include "User.hpp"
#include <iostream>
#include "ExceptionHandling.hpp"
#include "Filter.hpp"
#include "CityFilter.hpp"
#include "StarFilter.hpp"
#include "PriceFilter.hpp"
#include "RoomFilter.hpp"
#include "DefaultPriceFilter.hpp"

#define BAD_REQUEST_ERROR "Bad Request"
#define PERMISSION_DENIED_ERROR "Permission Denied"
#define NOT_FOUND_ERROR "Not Found"
#define NOT_ENOUGH_ROOM_ERROR "Not Enough Room"
#define NOT_ENOUGH_CREDIT_ERROR "Not Enough Credit"
#define EMPTY_LIST "Empty"
#define DEFAULT_PRICE_ANNOUNCEMENT "* Results have been filtered by the default price filter.\n"

#define QUESTION_MARK "?"
#define POST_COMMAND "POST"
#define GET_COMMAND "GET"
#define DELETE_COMMAND "DELETE"
#define SIGNUP_COMMAND "signup"
#define USERNAME "username"
#define PASSWORD "password"
#define EMAIL "email"
#define LOGIN_COMMAND "login"
#define LOGOUT_COMMAND "logout"
#define WALLET_COMMAND "wallet"
#define AMOUNT "amount"
#define COUNT "count"
#define HOTELS_COMMAND "hotels"
#define ID "id"
#define FILTERS_COMMAND "filters"
#define CITY "city"
#define MIN_STAR "min_star"
#define MAX_STAR "max_star"
#define MIN_PRICE "min_price"
#define MAX_PRICE "max_price"
#define ROOM_TYPE "type"
#define QUANTITY "quantity"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define RESERVES_COMMAND "reserves"
#define HOTEL_ID "hotel"
#define COMMENTS_COMMAND "comments"
#define COMMENT "comment"
#define RATINGS_COMMAND "ratings"
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define OVERALL_RATING "overall_rating"
#define DEFAULT_PRICE_FILTER_COMMAND "default_price_filter"
#define SORT_COMMAND "sort"
#define MANUAL_WEIGHTS_COMMAND "manual_weights"
#define ESTIMATED_WEIGHTS_COMMAND "estimated_weights"
#define ACTIVE "active"
#define PROPERTY "property"
#define ORDER "order"

#define OK "OK\n"

typedef std::vector <std::pair <int, std::vector <std::string> > > Hotels_info;

bool is_between_1_and_5(double input);
bool comparing_hotels(Hotel* a, Hotel* b);
int empty_rooms_number(std::vector <Room*> selected_rooms, int check_in, int check_out);
std::vector <Room*> reservable_rooms(int check_in, int check_out,
                                     int quantity, std::vector <Room*> selected_rooms);
bool is_have_price_filter(std::vector <Filter*> filters);
bool is_have_default_price_filter(std::vector <Filter*> filters);
void active_default_price_filter(std::vector <Hotel*> &hotels, User* logged_in_user);

class UTRIP
{
private:
    std::vector <Hotel*> hotels;
    std::vector <User*> users;
    std::vector <Filter*> filters;
    std::vector <Hotel*> first_hotels;
    User* logged_in_user;

public:
    UTRIP(Hotels_info rows_information);

    void sign_up(std::string user_name, std::string email, std::string password);

    void login(std::string email, std::string password);

    void logout();

    void increase_balance(double amount);

    void reserve(std::string hotel_id, std::string room_kind, int quantity, int check_in, int check_out);

    void get_user_reserves();

    void get_turnover(int count);

    void show_hotels_info();

    void show_hotel_info(std::string hotel_id);

    void add_comment(std::string hotel_id, std::string comment);

    void show_comments(std::string hotel_id);

    void set_ratings(std::vector <std::pair <int, std::vector <std::string> > > ratings_information);

    void add_rating(std::string hotel_id, double location, double cleanliness,
                    double staff, double facilities, double value_for_money, double overall_rating);

    void show_rating(std::string hotel_id);

    Hotel* find_hotel_by_id(std::string hotel_id);

    void cancel_reservation(int reservation_id);

    void filter_city(std::string city);

    void filter_star(int min_star, int max_star);

    void filter_price(int min_price, int max_price);

    void filter_room(std::string room_type, int quantity, int check_in, int check_out);

    void default_price_filter(std::string activate_mode);

    void delete_filters();

    bool is_email_or_username_duplicate(std::string email, std::string user_name);

    bool is_email_or_pass_invalid(std::string email, std::string password);

    int duplicate_index(Filter* filter);

    bool is_default_price_filter_active();

    void sort_hotels(std::string property, std::string order);

    void set_manual_weights(double location, double cleanliness, double staff, double facilities, double value_for_money);

    void show_manual_weights();

    void deactive_manual_weights();

    void show_estimated_weights();
};





#endif

