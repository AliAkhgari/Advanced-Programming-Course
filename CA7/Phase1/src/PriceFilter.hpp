#ifndef __PRICE_FILTER_H__
#define __PRICE_FILTER_H__ "__PRICE_FILTER_H__"

#include "Filter.hpp"

class PriceFilter : public Filter
{
private:
    int min_price;
    int max_price;
    std::vector <Hotel*> filtered_hotels;

public:
    PriceFilter(int min_price_, int max_price_)
    {
        min_price = min_price_;
        max_price = max_price_;
    }

    virtual void apply_filter(std::vector <Hotel*> &hotels);

    virtual std::string get_kind () { return "price"; }
};

#endif