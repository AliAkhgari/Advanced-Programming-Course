#ifndef __FILTER_H__
#define __FILTER_H__ "__FILTER_H__"

#include "Hotel.hpp"

class Filter
{
private:
    std::string kind;
    
public:
    virtual std::string get_kind () = 0;

    virtual void apply_filter(std::vector <Hotel*> &hotels) = 0;

};


#endif
