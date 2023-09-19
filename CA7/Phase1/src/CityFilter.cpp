#include "CityFilter.hpp"

using namespace std;

void CityFilter::apply_filter(std::vector <Hotel*> &hotels)
{
    filtered_hotels.clear();
    for(int i = 0; i < hotels.size(); i++)
    {
        if(hotels[i]->get_city() == city)
            filtered_hotels.push_back(hotels[i]);
    }
    hotels = filtered_hotels;
}