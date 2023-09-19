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
             << setprecision(2) << average_price /*<< SEPERATOR*/ << endl;
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

void Hotel::set_rating(Score location, Score cleanliness, Score staff,
                       Score facilities, Score value_for_money, Score overall_rating)
{
    average_ratings = Ratings(location, cleanliness, staff,
                              facilities, value_for_money, overall_rating);
}

void Hotel::add_rating(Name user_name, Score location, Score cleanliness, Score staff,
                Score facilities, Score value_for_money, Score overall_rating)
{
    if(!has_first(user_name))
    {
        users_rating.push_back(Rating(user_name, location, cleanliness, staff,
                                      facilities, value_for_money, overall_rating));
    }
    else
    {
        int index = first_index(user_name);
        users_rating[index] = Rating(user_name, location, cleanliness, staff,
                                     facilities, value_for_money, overall_rating);
    }
}

int Hotel::first_index(Name user_name)
{
    for(int i = 0; i < users_rating.size(); i++)
        if(user_name == users_rating[i].get_user_name())
            return i;

    return users_rating.size();
}

void Hotel::show_rating()
{
    cout << fixed;
    cout << LOCATION_PRINT << setprecision(2) << average_ratings.location << CLEANLINESS_PRINT 
         << setprecision(2) << average_ratings.cleanliness << STAFF_PRINT << average_ratings.staff
         << FACILITIES_PRINT << average_ratings.facilities << VALUE_FOR_MONEY_PRINT
         << average_ratings.value_for_money << OVERALL_RATING_PRINT
         << average_ratings.overall_rating << endl;
}

bool Hotel::has_first(Name user_name)
{
    for(int i = 0; i < users_rating.size(); i++)
        if(user_name == users_rating[i].get_user_name())
            return true;
    
    return false;
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

double Hotel::user_overall_rating(string name, vector <double> manual_weights)
{
    for(int i = 0; i < users_rating.size(); i++)
        if(users_rating[i].get_user_name() == name)
            return users_rating[i].get_overall_rating();
    
    double sum = average_ratings.location * manual_weights[0] + average_ratings.cleanliness * manual_weights[1] +
                 average_ratings.staff * manual_weights[2] + average_ratings.facilities * manual_weights[3] +
                 average_ratings.value_for_money * manual_weights[4];
    double weights_sum = 0;
    for(int i = 0; i < manual_weights.size(); i++)
        weights_sum += manual_weights[i];

    return sum / weights_sum;
}

double Hotel::personal_overall_rating(string name, vector <double> weights)
{    
    for(int i = 0; i < users_rating.size(); i++)
        if(users_rating[i].get_user_name() == name)
            return users_rating[i].get_overall_rating();

    double sum = average_ratings.location * weights[0] + average_ratings.cleanliness * weights[1] +
                 average_ratings.staff * weights[2] + average_ratings.facilities * weights[3] +
                 average_ratings.value_for_money * weights[4];
    double weights_sum = 0;
    for(int i = 0; i < weights.size(); i++)
        weights_sum += weights[i];

    return sum / weights_sum;
}