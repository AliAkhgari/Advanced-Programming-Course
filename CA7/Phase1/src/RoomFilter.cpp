#include "RoomFilter.hpp"

using namespace std;

void RoomFilter::apply_filter(std::vector <Hotel*> &hotels)
{
    filtered_hotels.clear();
    for(int i = 0; i < hotels.size(); i++)
    {
        vector <Room*> selected_rooms = hotels[i]->find_rooms_by_kind(room_type);

        vector <Room*> reserved_rooms;
        int empty_rooms = 0;
        for(int i = 0; i < selected_rooms.size(); i++)
        {
            if(selected_rooms[i]->is_empty(check_in, check_out))
                empty_rooms++;
        }
        if(selected_rooms.size() >= quantity && empty_rooms >= quantity)
            filtered_hotels.push_back(hotels[i]);
    }
    hotels = filtered_hotels;
}