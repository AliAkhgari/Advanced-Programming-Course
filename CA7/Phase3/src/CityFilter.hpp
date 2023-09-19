#ifndef __CITY_FILTER_H__
#define __CITY_FILTER_H__ "__CITY_FILTER_H__"

#include "Filter.hpp"
#include "Hotel.hpp"
#include <vector>
#include <iostream>
#include <string>

class CityFilter : public Filter
{
private:
    std::string city;
    std::vector <Hotel*> filtered_hotels;

public:
    CityFilter(std::string city_)
    {
        city = city_;
    }

    virtual void apply_filter(std::vector <Hotel*> &hotels);

    virtual std::string get_kind () { return "city"; }
};


#endif