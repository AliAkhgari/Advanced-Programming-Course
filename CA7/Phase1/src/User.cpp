#include "User.hpp"

using namespace std;

User::User(string user_name_, string email_, string password_)
{
    user_name = user_name_;
    email = email_;
    password = generate_hash(password_);
    balance = 0;
    reservation_id = 1;
    turnover.push_back(balance);
}

User* User::logged_in(string user_email, string user_password)
{
    if(email == user_email && generate_hash(user_password) == password)
        return this;
    else
        return NULL;
}

void User::increase_balance(double amount)
{
    balance += amount;
    turnover.push_back(balance);
}

void User::make_reservation(vector <Room*> rooms, string hotel_id, string room_kind,
                        int quantity, int cost, int check_in, int check_out)
{
    Reserve* new_reservation = new Reserve(rooms, reservation_id, hotel_id, room_kind, quantity, cost, check_in, check_out);
    reserves.push_back(new_reservation);
    balance -= cost;
    turnover.push_back(balance);
    new_reservation->print_reserved_rooms();
    reservation_id++;
}

void User::cancel_reservation(int reservation_id)
{
    Reserve* selected_reserve = find_reserve_by_id(reservation_id);
    if(selected_reserve == NULL)
        throw ExceptionHandling(NOT_FOUND_ERROR);

    selected_reserve->empty_rooms();
    balance += selected_reserve->get_cost() / 2;
    turnover.push_back(balance);
    delete selected_reserve;
    reserves.erase(remove(reserves.begin(), reserves.end(), selected_reserve), reserves.end());
}

void User::print_turnover(int count)
{
    if(count < 0)
        throw ExceptionHandling(BAD_REQUEST_ERROR);

    if(count > turnover.size())
        count = turnover.size();

    int x = turnover.size() - count;
    for(int i = turnover.size() - 1; i >= x; i--)
        cout << (int)turnover[i] << endl;
}

void User::print_reserves()
{
    if(reserves.size() == 0)
        cout << EMPTY_LIST << endl;
    else
        for(int i = reserves.size() - 1; i >= 0; i--)
            reserves[i]->print_info();
}

Reserve* User::find_reserve_by_id(int reservation_id)
{
    for(int i = 0; i < reserves.size(); i++)
        if(reserves[i]->get_reservation_id() == reservation_id)
            return reserves[i];
            
    return NULL;
}

unsigned long int generate_hash(string password)
{
    return hash<string>()(password);
}