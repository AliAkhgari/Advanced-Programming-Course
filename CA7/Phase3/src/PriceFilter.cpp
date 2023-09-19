#include "PriceFilter.hpp"

using namespace std;

void PriceFilter::apply_filter(std::vector <Hotel*> &hotels)
{
    filtered_hotels.clear();
    for(int i = 0; i < hotels.size(); i++)
    {
        if(hotels[i]->get_average_price() >= min_price && hotels[i]->get_average_price() <= max_price)
            filtered_hotels.push_back(hotels[i]);
    }
    hotels = filtered_hotels;
}