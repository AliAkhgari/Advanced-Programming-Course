#ifndef __RESERVE_H__
#define __RESERVE_H__ "__RESERVE_H__"

#include "Room.hpp"
#include <vector>
#include <string>
#include <iostream>

#define ID_PRINT "id: "
#define HOTEL_PRINT " hotel: "
#define ROOM_PRINT " room: "
#define QUANTITY_PRINT " quantity: "
#define COST_PRINT " cost: "
#define CHECKIN_PRINT " check_in "
#define CHECKOUT_PRINT " check_out "

typedef std::vector <Room*> Rooms;

class Reserve
{
private:
    Rooms reserved_rooms;
    int reservation_id;
    std::string hotel_id;
    std::string room_kind;
    int quantity;
    int cost;
    int check_in;
    int check_out;

public:
    Reserve(Rooms reserved_rooms_, int reservation_id_, std::string hotel_id_, std::string room_kind_,
            int quantity_, int cost_, int check_in_, int check_out_);

    void print_reserved_rooms();

    void print_info();

    int get_reservation_id () { return reservation_id; }

    int get_cost () { return cost; }

    int get_quantity() { return quantity; }

    void empty_rooms();

    double average_cost();

    double get_room_price() { return reserved_rooms[0]->get_room_cost(); }
};



#endif