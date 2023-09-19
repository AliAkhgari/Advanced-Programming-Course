#include "Room.hpp"

using namespace std;

Room::Room(string id_, string room_kind_, int room_price_)
{
    id = id_;
    room_kind = room_kind_;
    room_price = room_price_;
}

void Room::reserve_room(int check_in, int check_out)
{
    for(int i = check_in; i <= check_out; i++)
    {
        reserved_days.push_back(i);
    }
}

bool Room::is_empty(int check_in, int check_out)
{
    for(int i = check_in; i <= check_out; i++)
    {
        for(int j = 0; j < reserved_days.size(); j++)
        {
            if(i == reserved_days[j])
                return false;
        }
    }
    return true;
}

void Room::empty_reserved_days(int check_in, int check_out)
{
    for(int i = check_in; i <= check_out; i++)
    {
        reserved_days.erase(remove(reserved_days.begin(), reserved_days.end(), i), reserved_days.end());
    }
}