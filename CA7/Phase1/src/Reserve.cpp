#include "Reserve.hpp"

using namespace std;

Reserve::Reserve(Rooms reserved_rooms_, int reservation_id_, string hotel_id_, string room_kind_,
        int quantity_, int cost_, int check_in_, int check_out_)
        {
            reserved_rooms = reserved_rooms_;
            reservation_id = reservation_id_;
            hotel_id = hotel_id_;
            room_kind = room_kind_;
            quantity = quantity_;
            cost = cost_;
            check_in = check_in_;
            check_out = check_out_;
        }

void Reserve::print_reserved_rooms()
{
    for(int i = 0; i < reserved_rooms.size(); i++)
    {
        cout << reserved_rooms[i]->get_id();
        if(i != reserved_rooms.size() - 1)
            cout << " ";
    }
    cout << endl;
}

void Reserve::print_info()
{
    cout << ID_PRINT << reservation_id << HOTEL_PRINT << hotel_id << ROOM_PRINT << room_kind
    << QUANTITY_PRINT << quantity << COST_PRINT << cost << CHECKIN_PRINT <<
    check_in << CHECKOUT_PRINT << check_out << endl; 
}

void Reserve::empty_rooms()
{
    for(int i = 0; i < reserved_rooms.size(); i++)
    {
        reserved_rooms[i]->empty_reserved_days(check_in, check_out);
    }
    reserved_rooms.clear();
}
