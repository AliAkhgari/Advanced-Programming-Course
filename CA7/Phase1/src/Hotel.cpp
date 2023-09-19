#include "Hotel.hpp"

using namespace std;

Hotel::Hotel(vector <string> hotel_info)
{
    unique_id = hotel_info[0];
    name = hotel_info[1];
    star_rating = stoi(hotel_info[2]);
    overview = hotel_info[3];
    property_amenities = hotel_info[4];
    city = hotel_info[5];
    latitude = stod(hotel_info[6]);
    longitude = stod(hotel_info[7]);
    imgage_url = hotel_info[8];
    rooms_information = RoomsInfo(stoi(hotel_info[9]), stoi(hotel_info[10]), stoi(hotel_info[11]),
                                  stoi(hotel_info[12]), stoi(hotel_info[13]), stoi(hotel_info[14]),
                                  stoi(hotel_info[15]), stoi(hotel_info[16]));

    average_price = price_average(rooms_information.standard_room_price, rooms_information.deluxe_room_price,
                                  rooms_information.luxury_room_price, rooms_information.premium_room_price);
    total_num_of_rooms = rooms_information.num_of_standard_rooms + rooms_information.num_of_deluxe_rooms +
                         rooms_information.num_of_luxury_rooms + rooms_information.num_of_premium_rooms;

    for(int i = 0; i < rooms_information.num_of_standard_rooms; i++)
    {
        string room_id = STANDARD_ROOM_SIGN + to_string(i + 1);
        Room* new_room = new Room(room_id, STANDARD_ROOM, rooms_information.standard_room_price);
        rooms_information.standard_rooms.push_back(new_room);
    }
    for(int i = 0; i < rooms_information.num_of_deluxe_rooms; i++)
    {
        string room_id = DELUXE_ROOM_SIGN + to_string(i + 1);
        Room* new_room = new Room(room_id, DELUXE_ROOM, rooms_information.deluxe_room_price);
        rooms_information.deluxe_rooms.push_back(new_room);
    }
    for(int i = 0; i < rooms_information.num_of_luxury_rooms; i++)
    {
        string room_id = LUXURY_ROOM_SIGN + to_string(i + 1);
        Room* new_room = new Room(room_id, LUXURY_ROOM, rooms_information.luxury_room_price);
        rooms_information.luxury_rooms.push_back(new_room);
    }
    for(int i = 0; i < rooms_information.num_of_premium_rooms; i++)
    {
        string room_id = PREMIUM_ROOM_SIGN + to_string(i + 1);
        Room* new_room = new Room(room_id, PREMIUM_ROOM, rooms_information.premium_room_price);
        rooms_information.premium_rooms.push_back(new_room);
    }
}

Hotel::~Hotel()
{
    for (auto p : rooms_information.standard_rooms)
        delete p;
    rooms_information.standard_rooms.clear();

    for (auto p : rooms_information.deluxe_rooms)
        delete p;
    rooms_information.deluxe_rooms.clear();

    for (auto p : rooms_information.luxury_rooms)
        delete p;
    rooms_information.luxury_rooms.clear();
    
    for (auto p : rooms_information.premium_rooms)
        delete p;
    rooms_information.premium_rooms.clear();
}

Rooms Hotel::find_rooms_by_kind(string room_kind)
{
    if(room_kind == STANDARD_ROOM)
        return rooms_information.standard_rooms;
    if(room_kind == DELUXE_ROOM)
        return rooms_information.deluxe_rooms;
    if(room_kind == LUXURY_ROOM)
        return rooms_information.luxury_rooms;
    if(room_kind == PREMIUM_ROOM)
        return rooms_information.premium_rooms;
    else
        throw ExceptionHandling(BAD_REQUEST_ERROR);
}

Price Hotel::room_price(string room_kind)
{
    if(room_kind == STANDARD_ROOM)
        return rooms_information.standard_room_price;
    else if(room_kind == DELUXE_ROOM)
        return rooms_information.deluxe_room_price;
    else if(room_kind == LUXURY_ROOM)
        return rooms_information.luxury_room_price;
    else
        return rooms_information.premium_room_price;
}

void Hotel::print(string mode)
{
    cout << fixed;
    if(mode == "all")
    {
        cout << unique_id << SEPERATOR << name << SEPERATOR << star_rating << SEPERATOR << city << SEPERATOR 
             << total_num_of_rooms << SEPERATOR 
             << setprecision(2) << average_price << SEPERATOR << endl;
    }
    else
    {
        cout << unique_id << "\n" << name << STAR_PRINT << star_rating << OVERVIEW_PRINT
             << overview << AMENITIES_PRINT << property_amenities << CITY_PRINT << city 
             << LATITUDE_PRINT << setprecision(2) << latitude << LONGITUDE_PRINT 
             << setprecision(2) << longitude << ROOMS_NUMBER_PRINT
             << rooms_information.num_of_standard_rooms << SEPERATOR << rooms_information.num_of_deluxe_rooms << SEPERATOR
             << rooms_information.num_of_luxury_rooms << SEPERATOR << rooms_information.num_of_premium_rooms << ROOMS_PRICE_PRINT
             << rooms_information.standard_room_price << SEPERATOR << rooms_information.deluxe_room_price << SEPERATOR
             << rooms_information.luxury_room_price << SEPERATOR << rooms_information.premium_room_price << endl;
    }
}

void Hotel::add_comment(Name user_name, string comment)
{
    comments.push_back(UserComment(user_name, comment));
}

void Hotel::show_comments()
{
    for(int i = comments.size() - 1; i >= 0; i--)
        cout << comments[i].user_name << ": " << comments[i].comment << endl;
}

void Hotel::add_rating(Name user_name, Score location, Score cleanliness, Score staff,
                Score facilities, Score value_for_money, Score overall_rating)
{
    if(!has_first(user_name))
    {
        ratings.push_back(UserRatings(user_name, location, cleanliness, staff,
                                      facilities, value_for_money, overall_rating));
    }
    else
    {
        int index = first_index(user_name);
        ratings[index] = UserRatings(user_name, location, cleanliness, staff,
                                     facilities, value_for_money, overall_rating);
    }
}

void Hotel::show_rating()
{
    if(ratings.size() == 0)
        throw ExceptionHandling(NO_RATING_ERROR);

    cout << fixed;
    cout << LOCATION_PRINT << setprecision(2) << average_rating(LOCATION) << CLEANLINESS_PRINT 
         << average_rating(CLEANLINESS) << STAFF_PRINT << average_rating(STAFF)
         << FACILITIES_PRINT << average_rating(FACILITIES) << VALUE_FOR_MONEY_PRINT
         << average_rating(VALUE_FOR_MONEY_TYPE) << OVERALL_RATING_PRINT
         << average_rating(OVERALL_RATING_TYPE) << endl;

}

bool Hotel::has_first(Name user_name)
{
    for(int i = 0; i < ratings.size(); i++)
        if(user_name == ratings[i].user_name)
            return true;
    
    return false;
}   

int Hotel::first_index(Name user_name)
{
    for(int i = 0; i < ratings.size(); i++)
        if(user_name == ratings[i].user_name)
            return i;

    return ratings.size();
}

double Hotel::average_rating(string rating_kind)
{
    double sum = 0;
    for(int i = 0; i < ratings.size(); i++)
    {
        if(rating_kind == LOCATION)
            sum += ratings[i].location;
        else if(rating_kind == CLEANLINESS)
            sum += ratings[i].cleanliness;
        else if(rating_kind == STAFF)
            sum += ratings[i].staff;
        else if(rating_kind == FACILITIES)
            sum += ratings[i].facilities;
        else if(rating_kind == VALUE_FOR_MONEY_TYPE)
            sum += ratings[i].value_for_money;
        else    
            sum += ratings[i].overall_rating;
    }

    return sum / ratings.size();
}

double price_average(double x, double y, double z, double t)
{
    vector <double> numbers{ x, y, z, t };
    double sum = 0;
    int size = 4;
    for(int i = 0; i < numbers.size(); i++)
    {
        sum += numbers[i];
        if(numbers[i] == 0)
            size--;
    }
    if(size == 0)
        size = 1;
    return sum/size;
}