#ifndef __DEFAULT_PRICE_FILTER_H__
#define __DEFAULT_PRICE_FILTER_H__ "__DEFAULT_PRICE_FILTER_H__"

#include "Filter.hpp"
#include "User.hpp"

class DefaultPriceFilter : public Filter
{
private:
    User* logged_in_user;
    std::vector <Hotel*> filtered_hotels;

public:
    DefaultPriceFilter(User* logged_in_user_)
    {
        logged_in_user = logged_in_user_;
    }

    virtual void apply_filter(std::vector <Hotel*> &hotels);

    virtual std::string get_kind () { return "default_price"; }
};

#endif