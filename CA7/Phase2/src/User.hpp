#ifndef __USER_H__
#define __USER_H__ "__USER_H__"

#include <string>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>
#include <sstream>
#include "Reserve.hpp"
#include "ExceptionHandling.hpp"
#include "cmath"
#include "Hotel.hpp"

#define BAD_REQUEST_ERROR "Bad Request"
#define PERMISSION_DENIED_ERROR "Permission Denied"
#define NOT_FOUND_ERROR "Not Found"
#define NOT_ENOUGH_ROOM_ERROR "Not Enough Room"
#define NOT_ENOUGH_CREDIT_ERROR "Not Enough Credit"
#define EMPTY_LIST "Empty"

#define EPSILON 0.00001
#define ID_PROPERTY "id"
#define NAME_PROPERTY "name"
#define STAR_RATING_PROPERTY "star_rating"
#define CITY_PROPERTY "city"
#define STANDARD_ROOM_PRICE_PROPERTY "standard_room_price"
#define DELUXE_ROOM_PRICE_PROPERTY "deluxe_room_price"
#define LUXURY_ROOM_PRICE_PROPERTY "luxury_room_price"
#define PREMIUM_ROOM_PRICE_PROPERTY "premium_room_price"
#define AVERAGE_ROOM_PRICE_PROPERTY "average_room_price"
#define RATING_OVERALL_PROPERTY "rating_overall"
#define RATING_PERSONAL_PROPERTY "rating_personal"
#define ASCENDING_ORDER "ascending"
#define DESCENDING_ORDER "descending"
#define INSUFFICIENT_RATINGS_ERROR "Insufficient Ratings"

unsigned long int generate_hash(std::string password);
void update_estimation_weights(std::vector <double> &weights, std::vector <double> d);
void update_d(std::vector <double> &d);
double random_number();
std::vector <double> random_weights();
double estimation_weights_overall(Rating rating, std::vector <double> weights);
double error(Rating rating, std::vector <double> weights);
double derivative(Rating rating, std::vector <double> weights, double overall_rating, int i);
double clip(double input, double lower, double upper);
std::vector <double> gradiant(std::vector <Rating> ratings, std::vector <double> weights);

class User
{
private:
    std::string user_name;
    std::string email;
    unsigned long int password;
    double balance;
    std::vector <double> turnover;
    std::vector <Reserve*> reserves;
    int reservation_id;
    std::vector <Rating> ratings;
    double reserves_average;
    double diviation;
    std::string sort_order;
    std::string sort_property;
    bool manual_weights_activation;
    std::vector <double> manual_weights;
    std::vector <double> estimation_weights;
public:

    User(std::string user_name_, std::string email_, std::string password_);

    User* logged_in(std::string user_email, std::string user_password);

    void increase_balance(double amount);

    void make_reservation(std::vector <Room*> rooms, std::string hotel_id, std::string room_kind,
                          int quantity, int cost, int check_in, int check_out);

    void cancel_reservation(int reservation_id);

    void print_turnover(int count);

    std::string get_user_name() { return user_name; }

    std::string get_email() { return email; }

    unsigned long int get_password () { return password; }

    double get_balance () { return balance; }

    void print_reserves();

    Reserve* find_reserve_by_id(int reservation_id);

    void update_divation();

    int get_reserves_number () { return reserves.size(); }

    double get_divation () { return diviation; }

    double get_reserves_average () { return reserves_average; }

    bool activate_default_price_filter;

    void set_sorting_method(std::string property, std::string order);

    void sort_hotels(std::vector <Hotel*> &hotels);

    void set_manual_weights(double location, double cleanliness, double staff, double facilities, double value_for_money);

    void deactive_manual_weights();
    
    void print_manual_weights();

    void print_estimated_weights();

    double calc_overall_weights_rating(Hotel* input);

    void add_rating(std::string hotel_id, double location, double cleanliness,
                      double staff, double facilities, double value_for_money, double overall_rating);

    void calc_estimation_weights();

    void clear_info();
};



#endif