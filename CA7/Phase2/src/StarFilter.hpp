#ifndef __STAR_FILTER_H__
#define __STAR_FILTER_H__ "__STAR_FILTER_H__"

#include "Filter.hpp"

class StarFilter : public Filter
{
private:
    int min_star;
    int max_star;
    std::vector <Hotel*> filtered_hotels;

public:
    StarFilter(int min_star_, int max_star_)
    {
        min_star = min_star_;
        max_star = max_star_;
    }

    virtual void apply_filter(std::vector <Hotel*> &hotels);

    virtual std::string get_kind () { return "star"; }

};



#endif