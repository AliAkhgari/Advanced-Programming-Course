#include "StarFilter.hpp"

using namespace std;

void StarFilter::apply_filter(vector <Hotel*> &hotels)
{
    filtered_hotels.clear();
    for(int i = 0; i < hotels.size(); i++)
    {
        if(hotels[i]->get_star() >= min_star && hotels[i]->get_star() <= max_star)
            filtered_hotels.push_back(hotels[i]);
    }
    hotels = filtered_hotels;
}
