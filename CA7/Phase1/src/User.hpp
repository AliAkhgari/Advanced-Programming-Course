#ifndef __USER_H__
#define __USER_H__ "__USER_H__"

#include <string>
#include <vector>
#include <functional>
#include "Reserve.hpp"
#include "Filter.hpp"
#include "CityFilter.hpp"
#include "StarFilter.hpp"
#include "cmath"

#define BAD_REQUEST_ERROR "Bad Request"
#define PERMISSION_DENIED_ERROR "Permission Denied"
#define NOT_FOUND_ERROR "Not Found"
#define NOT_ENOUGH_ROOM_ERROR "Not Enough Room"
#define NOT_ENOUGH_CREDIT_ERROR "Not Enough Credit"
#define EMPTY_LIST "Empty"

unsigned long int generate_hash(std::string password);

class User
{
private:
    std::string user_name;
    std::string email;
    // std::string password;
    unsigned long int password;
    double balance;
    std::vector <double> turnover;
    std::vector <Reserve*> reserves;
    int reservation_id;
    
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

};



#endif