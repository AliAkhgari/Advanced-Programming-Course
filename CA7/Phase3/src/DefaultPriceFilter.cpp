#include "DefaultPriceFilter.hpp"

using namespace std;

void DefaultPriceFilter::apply_filter(std::vector <Hotel*> &hotels)
{
    filtered_hotels.clear();
    for(int i = 0; i < hotels.size(); i++)
    {
        // cout << "\nreserves_average : " << logged_in_user->get_reserves_average();
        // cout << "hotel_average_price : " << hotels[i]->get_average_price()
        //      << "\nreserves_average : " << logged_in_user->get_reserves_average()
        //      << "\ndivation : " << logged_in_user->get_divation() << "\n";
        //      cout << "Cdcdscscsdccdcsc" << endl;
        if(fabs(hotels[i]->get_average_price() - logged_in_user->get_reserves_average()) <= 2 * logged_in_user->get_divation())
            filtered_hotels.push_back(hotels[i]);
    }
    hotels = filtered_hotels;
}
