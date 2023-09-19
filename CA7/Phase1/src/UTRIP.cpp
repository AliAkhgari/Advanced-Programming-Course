#include "UTRIP.hpp"

using namespace std;

UTRIP::UTRIP(Hotels_info rows_information)
{
    for(int i = 0; i < rows_information.size() - 1; i++)
    {
        Hotel* new_hotel = new Hotel(rows_information[i].second);
        hotels.push_back(new_hotel);
    }
    first_hotels = hotels;
    logged_in_user = NULL;
}

void UTRIP::sign_up(string user_name, string email, string password)
{
    if(logged_in_user != NULL)
        throw ExceptionHandling(BAD_REQUEST_ERROR);
    if(is_email_or_username_duplicate(email, user_name))
        throw ExceptionHandling(BAD_REQUEST_ERROR);

    User* new_user = new User(user_name, email, password);
    users.push_back(new_user);
    logged_in_user = new_user;
}

void UTRIP::login(string email, string password)
{
    if(logged_in_user != NULL)
        throw ExceptionHandling(BAD_REQUEST_ERROR);
    if(is_email_or_pass_invalid(email, password))
        throw ExceptionHandling(BAD_REQUEST_ERROR);

    for(int i = 0; i < users.size(); i++)
        if(users[i]->logged_in(email, password) != NULL)
            logged_in_user = users[i]->logged_in(email, password);
}

void UTRIP::logout()
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);

    filters.clear();
    hotels = first_hotels;
    logged_in_user = NULL;
}

void UTRIP::increase_balance(double amount)
{
    if(amount <= 0)
        throw ExceptionHandling(BAD_REQUEST_ERROR);
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);

    logged_in_user->increase_balance(amount);
}

void UTRIP::reserve(string hotel_id, string room_kind, int quantity, int check_in, int check_out)
{
    Hotel* selected_hotel = find_hotel_by_id(hotel_id);

    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
    if(selected_hotel == NULL)
        throw ExceptionHandling (NOT_FOUND_ERROR);
    if(quantity <= 0)
        throw ExceptionHandling (BAD_REQUEST_ERROR);
    if(check_in < 1 || check_out > 30 || check_in > check_out)
        throw ExceptionHandling (BAD_REQUEST_ERROR);

    vector <Room*> selected_rooms = selected_hotel->find_rooms_by_kind(room_kind);
    int empty_rooms = empty_rooms_number(selected_rooms, check_in, check_out);
    int all_rooms_cost = (check_out - check_in + 1) * quantity * selected_hotel->room_price(room_kind);
    // cout << "empty_rooms : " << empty_rooms << endl;
    if(logged_in_user->get_balance() < all_rooms_cost)
        throw ExceptionHandling(NOT_ENOUGH_CREDIT_ERROR);
    if(selected_rooms.size() < quantity)
        throw ExceptionHandling(NOT_ENOUGH_ROOM_ERROR);
    if(empty_rooms < quantity)
        throw ExceptionHandling(NOT_ENOUGH_ROOM_ERROR);
    
    vector <Room*> reserved_rooms = reservable_rooms(check_in, check_out, quantity, selected_rooms);
    for(int i = 0; i < reserved_rooms.size(); i++)
        reserved_rooms[i]->reserve_room(check_in, check_out);
    logged_in_user->make_reservation(reserved_rooms, hotel_id, room_kind,
                                    quantity, all_rooms_cost, check_in, check_out);
}

int empty_rooms_number(vector <Room*> selected_rooms, int check_in, int check_out)
{
    int empty_rooms = 0;
    for(int i = 0; i < selected_rooms.size(); i++)
        if(selected_rooms[i]->is_empty(check_in, check_out))
            empty_rooms++;

    return empty_rooms;
}

vector <Room*> reservable_rooms(int check_in, int check_out, int quantity, vector <Room*> selected_rooms)
{
    vector <Room*> reserved_rooms;
    int counter = 0;
    for(int i = 0; i < selected_rooms.size(); i++)
    {
        if(counter >= quantity)
            break;
        if(selected_rooms[i]->is_empty(check_in, check_out))
        {
            reserved_rooms.push_back(selected_rooms[i]);
            counter++;
        }
    }
    return reserved_rooms;
}

void UTRIP::get_user_reserves()
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);

    logged_in_user->print_reserves();
}

void UTRIP::get_turnover(int count)
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
        
    logged_in_user->print_turnover(count);
}

void UTRIP::show_hotels_info()
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
    hotels = first_hotels;
    for(int i = 0; i < filters.size(); i++)
            filters[i]->apply_filter(hotels);
    if(hotels.size())
    {
        sort(hotels.begin(), hotels.end(), comparing_hotels);
        for(int i = 0; i < hotels.size(); i++)
            hotels[i]->print("all");
    }
    else
        cout << EMPTY_LIST << endl;
}

void UTRIP::show_hotel_info(string hotel_id)
{
    Hotel* selected_hotel = find_hotel_by_id(hotel_id);

    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
    if(selected_hotel == NULL)
        throw ExceptionHandling (NOT_FOUND_ERROR);
        
    selected_hotel->print("one");
}

void UTRIP::add_comment(string hotel_id, string comment)
{
    Hotel* selected_hotel = find_hotel_by_id(hotel_id);

    if(selected_hotel == NULL)
        throw ExceptionHandling(NOT_FOUND_ERROR);
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);

    selected_hotel->add_comment(logged_in_user->get_user_name(), comment);
}

void UTRIP::show_comments(string hotel_id)
{
    Hotel* selected_hotel = find_hotel_by_id(hotel_id);

    if(selected_hotel == NULL)
        throw ExceptionHandling(NOT_FOUND_ERROR);
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
    
    selected_hotel->show_comments();
}

void UTRIP::add_rating(string hotel_id, double location, double cleanliness,
                double staff, double facilities, double value_for_money, double overall_rating)
{
    Hotel* selected_hotel = find_hotel_by_id(hotel_id);

    if(!is_between_1_and_5(location) || !is_between_1_and_5(cleanliness) || !is_between_1_and_5(staff) ||
        !is_between_1_and_5(facilities) || !is_between_1_and_5(value_for_money) || !is_between_1_and_5(overall_rating))
        throw ExceptionHandling(BAD_REQUEST_ERROR);
    if(selected_hotel == NULL)
        throw ExceptionHandling(NOT_FOUND_ERROR);
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);

    selected_hotel->add_rating(logged_in_user->get_user_name(), location, cleanliness, staff, facilities, value_for_money, overall_rating);
}

void UTRIP::show_rating(string hotel_id)
{
    Hotel* selected_hotel = find_hotel_by_id(hotel_id);
    if(selected_hotel == NULL)
        throw ExceptionHandling(NOT_FOUND_ERROR);
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
    
    selected_hotel->show_rating();
}

Hotel* UTRIP::find_hotel_by_id(string hotel_id)
{
    for(int i = 0; i < first_hotels.size(); i++)
    {
        if(first_hotels[i]->get_id() == hotel_id) 
            return first_hotels[i];
    }
    return NULL;
}

void UTRIP::cancel_reservation(int reservation_id)
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);

    logged_in_user->cancel_reservation(reservation_id);
}

void UTRIP::filter_city(string city)
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
        
    CityFilter* new_city_filter = new CityFilter(city);
    if(duplicate_index(new_city_filter) == -1)
        filters.push_back(new_city_filter);
    else
        filters[duplicate_index(new_city_filter)] = new_city_filter;

}

void UTRIP::filter_star(int min_star, int max_star)
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
    if(min_star < 1 || max_star > 5 || min_star > max_star)
        throw ExceptionHandling(BAD_REQUEST_ERROR);

    StarFilter* new_star_filter = new StarFilter(min_star, max_star);
    if(duplicate_index(new_star_filter) == -1)
        filters.push_back(new_star_filter);
    else
        filters[duplicate_index(new_star_filter)] = new_star_filter;

}

void UTRIP::filter_price(int min_price, int max_price)
{
    if(min_price < 0 || max_price < 0 || max_price < min_price)
        throw ExceptionHandling(BAD_REQUEST_ERROR);
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);

    PriceFilter* new_price_filter = new PriceFilter(min_price, max_price);
    if(duplicate_index(new_price_filter) == -1)
        filters.push_back(new_price_filter);
    else
        filters[duplicate_index(new_price_filter)] = new_price_filter;

}

void UTRIP::filter_room(string room_type, int quantity, int check_in, int check_out)
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);
    if(quantity <= 0)
        throw ExceptionHandling (BAD_REQUEST_ERROR);

    RoomFilter* new_room_filter = new RoomFilter(room_type, quantity, check_in, check_out);
    if(duplicate_index(new_room_filter) == -1)
        filters.push_back(new_room_filter);
    else
        filters[duplicate_index(new_room_filter)] = new_room_filter;

}

void UTRIP::delete_filters()
{
    if(logged_in_user == NULL)
        throw ExceptionHandling(PERMISSION_DENIED_ERROR);

    filters.clear();
    hotels = first_hotels;
}

bool UTRIP::is_email_or_username_duplicate(string email, string user_name)
{
    for(int i = 0; i < users.size(); i++)
        if(users[i]->get_user_name() == user_name || users[i]->get_email() == email)
            return true;

    return false;
}

bool UTRIP::is_email_or_pass_invalid(string email, string password)
{
    for(int i = 0; i < users.size(); i++)
        if(users[i]->get_password() == generate_hash(password) && users[i]->get_email() == email)
            return false;

    return true;
}

int UTRIP::duplicate_index(Filter* filter)
{
    for(int i = 0; i < filters.size(); i++)
        if(filters[i]->get_kind() == filter->get_kind())
            return i;

    return -1;
}

bool is_between_1_and_5(double input)
{
    if(input >= 1 && input <= 5)
        return true;
    
    return false;
}

bool comparing_hotels(Hotel* a, Hotel* b)
{
    return a->get_id() < b->get_id();
}