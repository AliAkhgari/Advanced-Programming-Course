#ifndef __ROOM_H__
#define __ROOM_H__ "__ROOM_H__"

#include <string>
#include <vector>

class Room
{
private:
    std::string id;
    std::string room_kind;
    int room_price;
    std::vector <int> reserved_days;

public:
    Room(std::string id_, std::string room_kind_, int room_price_);

    void reserve_room(int check_in, int check_out);

    bool is_empty(int check_in, int check_out);

    int get_room_cost () { return room_price; }
    
    std::string get_id () { return id; }

    void empty_reserved_days(int check_in, int check_out);

};


#endif