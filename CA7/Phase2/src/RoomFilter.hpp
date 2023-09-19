#ifndef __ROOM_FILTER_H__
#define __ROOM_FILTER_H__ "__ROOM_FILTER_H__"

#include "Filter.hpp"

class RoomFilter : public Filter
{
private:
    std::string room_type;
    int quantity;
    int check_in;
    int check_out;
    std::vector <Hotel*> filtered_hotels;

public:
    RoomFilter(std::string room_type_, int quantity_, int check_in_, int check_out_)
    {
        room_type = room_type_;
        quantity = quantity_;
        check_in = check_in_;
        check_out = check_out_;
    }

    virtual void apply_filter(std::vector <Hotel*> &hotels);

    virtual std::string get_kind () { return "room"; }
    
};


#endif