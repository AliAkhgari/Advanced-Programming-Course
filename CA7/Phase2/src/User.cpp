#include "User.hpp"

using namespace std;

User::User(string user_name_, string email_, string password_)
{
    user_name = user_name_;
    email = email_;
    password = generate_hash(password_);
    balance = 0;
    reservation_id = 1;
    diviation = 0;
    reserves_average = 0;
    activate_default_price_filter = true;
    manual_weights_activation = false;
    turnover.push_back(balance);
}

void User::clear_info()
{
    manual_weights.clear();
    estimation_weights.clear();
    sort_order.clear();
    sort_property.clear();
    manual_weights_activation = false;
}

User* User::logged_in(string user_email, string user_password)
{
    if(email == user_email && generate_hash(user_password) == password)
    {
        activate_default_price_filter = true;
        return this;
    }
    else
        return NULL;
}

void User::increase_balance(double amount)
{
    balance += amount;
    turnover.push_back(balance);
}

void User::make_reservation(vector <Room*> rooms, string hotel_id, string room_kind,
                        int quantity, int cost, int check_in, int check_out)
{
    Reserve* new_reservation = new Reserve(rooms, reservation_id, hotel_id, room_kind, quantity, cost, check_in, check_out);
    reserves.push_back(new_reservation);
    update_divation();
    balance -= cost;
    turnover.push_back(balance);
    new_reservation->print_reserved_rooms();
    reservation_id++;
}

void User::cancel_reservation(int reservation_id)
{
    Reserve* selected_reserve = find_reserve_by_id(reservation_id);
    if(selected_reserve == NULL)
        throw ExceptionHandling(NOT_FOUND_ERROR);

    selected_reserve->empty_rooms();
    balance += selected_reserve->get_cost() / 2;
    turnover.push_back(balance);
    delete selected_reserve;
    reserves.erase(remove(reserves.begin(), reserves.end(), selected_reserve), reserves.end());
    update_divation();
}

void User::print_turnover(int count)
{
    if(count < 0)
        throw ExceptionHandling(BAD_REQUEST_ERROR);

    if(count > turnover.size())
        count = turnover.size();

    int x = turnover.size() - count;
    for(int i = turnover.size() - 1; i >= x; i--)
        cout << (int)turnover[i] << endl;
}

void User::print_reserves()
{
    if(reserves.size() == 0)
        cout << EMPTY_LIST << endl;
    else
        for(int i = reserves.size() - 1; i >= 0; i--)
            reserves[i]->print_info();
}

Reserve* User::find_reserve_by_id(int reservation_id)
{
    for(int i = 0; i < reserves.size(); i++)
        if(reserves[i]->get_reservation_id() == reservation_id)
            return reserves[i];
            
    return NULL;
}

void User::update_divation()
{
    double average;
    int all_rooms_number = 0;
    for(int i = 0; i < reserves.size(); i++)
    {
        average += reserves[i]->average_cost();
        all_rooms_number += reserves[i]->get_quantity();
    }
    average /= all_rooms_number;
    reserves_average = average;
    double sum = 0;
    for(int i = 0; i < reserves.size(); i++)
        for(int j = 0; j < reserves[i]->get_quantity(); j++)
            sum += pow(reserves[i]->get_room_price() - average, 2);
            
    diviation = sqrt(sum / (all_rooms_number - 1));
}

void User::set_sorting_method(string property, string order)
{
    if(order != ASCENDING_ORDER && order != DESCENDING_ORDER)
        throw ExceptionHandling(BAD_REQUEST_ERROR);
    if(property != ID_PROPERTY && property != NAME_PROPERTY && property != STAR_RATING_PROPERTY && property != CITY_PROPERTY && property != STANDARD_ROOM_PRICE_PROPERTY && property != DELUXE_ROOM_PRICE_PROPERTY && property == LUXURY_ROOM_PRICE_PROPERTY && property != PREMIUM_ROOM_PRICE_PROPERTY && property != AVERAGE_ROOM_PRICE_PROPERTY)
        throw ExceptionHandling(BAD_REQUEST_ERROR);

    sort_order = order;
    sort_property = property;
}

void initial_hotel_order(vector <Hotel*> &hotels)
{
    sort(hotels.begin(), hotels.end(), [](Hotel* a, Hotel* b) { return a->get_id() < b->get_id(); });
}

bool is_have_sort_command(string sort_property)
{
    if(sort_property.length())
        return true;
    return false;
}

void User::sort_hotels(vector <Hotel*> &hotels)
{
    initial_hotel_order(hotels);
    if(sort_property == RATING_PERSONAL_PROPERTY && ratings.size() < 5 && !manual_weights_activation)
        throw ExceptionHandling(INSUFFICIENT_RATINGS_ERROR);
    if(!is_have_sort_command(sort_property))
        return;
    string name = user_name;

    if(sort_property == ID_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_id() > b->get_id(); 
                                                                            else 
                                                                                return a->get_id() < b->get_id(); });
    else if(sort_property == NAME_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_name() > b->get_name(); 
                                                                            else 
                                                                                return a->get_name() < b->get_name(); });
    else if(sort_property == STAR_RATING_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_star() > b->get_star();
                                                                            else 
                                                                                    return a->get_star() < b->get_star(); });
    else if(sort_property == CITY_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_city() > b->get_city();
                                                                            else
                                                                                return a->get_city() < b->get_city(); });           
    else if(sort_property == STANDARD_ROOM_PRICE_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_standard_room_price() > b->get_standard_room_price(); 
                                                                            else
                                                                                return a->get_standard_room_price() < b->get_standard_room_price(); });
    else if(sort_property == DELUXE_ROOM_PRICE_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_deluxe_room_price() > b->get_deluxe_room_price(); 
                                                                            else
                                                                                return a->get_deluxe_room_price() < b->get_deluxe_room_price(); });
    else if(sort_property == LUXURY_ROOM_PRICE_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_luxury_room_price() > b->get_luxury_room_price(); 
                                                                            else 
                                                                                return a->get_luxury_room_price() < b->get_luxury_room_price(); });
    else if(sort_property == PREMIUM_ROOM_PRICE_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_premium_room_price() > b->get_premium_room_price(); 
                                                                            else 
                                                                                return a->get_premium_room_price() < b->get_premium_room_price(); });
    else if(sort_property == AVERAGE_ROOM_PRICE_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_average_price() > b->get_average_price(); 
                                                                            else 
                                                                                return a->get_average_price() < b->get_average_price(); });
    else if(sort_property == RATING_OVERALL_PROPERTY)
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->get_overall_rating() > b->get_overall_rating(); 
                                                                            else
                                                                                return a->get_overall_rating() < b->get_overall_rating(); });
    else if(sort_property == RATING_PERSONAL_PROPERTY && manual_weights_activation)
    {
        vector <double> weights = manual_weights;
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->user_overall_rating(name, weights) > b->user_overall_rating(name, weights); 
                                                                            else
                                                                                return a->user_overall_rating(name, weights) < b->user_overall_rating(name, weights); });
    }
    else if(sort_property == RATING_PERSONAL_PROPERTY && !manual_weights_activation)
    {
        calc_estimation_weights();
        vector <double> weights = estimation_weights;
        stable_sort(hotels.begin(), hotels.end(), [=](Hotel* a, Hotel* b) { if(sort_order == DESCENDING_ORDER)
                                                                                return a->personal_overall_rating(name, weights) > b->personal_overall_rating(name, weights); 
                                                                            else 
                                                                                return a->personal_overall_rating(name, weights) < b->personal_overall_rating(name, weights); });
    }
}

void User::set_manual_weights(double location, double cleanliness, double staff,
                        double facilities, double value_for_money)
{
    manual_weights_activation = true;
    manual_weights = { location, cleanliness, staff, facilities, value_for_money };
}

void User::deactive_manual_weights()
{
    manual_weights_activation = false;
}

double trucate(double input)
{
    return trunc(input * 100) / 100;
}

void User::print_manual_weights()
{
    if(manual_weights_activation == true)
    {
        cout << "active true " << setprecision(2) << fixed;
        cout << "location " << trucate(manual_weights[0]) << " cleanliness " 
            << trucate(manual_weights[1]) << " staff " << trucate(manual_weights[2])
            << " facilities " << trucate(manual_weights[3]) << " value_for_money "
            << trucate(manual_weights[4]) << endl;
    }
    else
        cout << "active false" << endl;
}

void User::print_estimated_weights()
{
    if(ratings.size() < 5)
        throw ExceptionHandling(INSUFFICIENT_RATINGS_ERROR);

    calc_estimation_weights();
    cout << setprecision(2) << fixed;
    cout << "location " << trucate(estimation_weights[0]) << " cleanliness " 
        << trucate(estimation_weights[1]) << " staff " << trucate(estimation_weights[2])
        << " facilities " << trucate(estimation_weights[3]) << " value_for_money "
        << trucate(estimation_weights[4]) << endl;
}

void User::add_rating(string hotel_id, double location, double cleanliness,
                      double staff, double facilities, double value_for_money, double overall_rating)
{
    ratings.push_back(Rating(hotel_id, location, cleanliness, staff, facilities, value_for_money, overall_rating));
}

double random_number()
{
    return rand() % 4 + 1;
}

vector <double> random_weights()
{
    vector <double> weights;
    for(int i = 0; i < 5; i++)
        weights.push_back(random_number());

    return weights;
}

double estimation_weights_overall(Rating rating, vector <double> weights)
{
    double sum = 0, weight_sum = 0;
    vector <double> ratings = rating.get_rating();
    for(int i = 0 ; i < 5; i++)
    {
        sum += weights[i] * ratings[i];
        weight_sum += weights[i];
    }
    return sum / weight_sum;
}

double error(Rating rating, vector <double> weights)
{
    return pow((estimation_weights_overall(rating, weights) - rating.get_overall_rating()), 2);
}

double derivative(Rating rating, vector <double> weights, double overall_rating, int i)
{
    vector <double> new_weights = weights;
    new_weights[i] += EPSILON;
    return (error(rating, new_weights) - error(rating, weights)) / EPSILON;
}

double clip(double input, double lower, double upper) 
{
    return max(lower, min(input, upper));
}

vector <double> gradiant(vector <Rating> ratings, vector <double> weights)
{
    vector <double> d(5);
    for(int i = 0; i < ratings.size(); i++)
        for(int j = 0; j < 5; j++)
            d[j] += derivative(ratings[i], weights, ratings[i].get_overall_rating(), j);

    return d;
}

void update_d(vector <double> &d)
{
    for(int i = 0; i < 5; i++)
        d[i] = 0;
}

void update_estimation_weights(vector <double> &weights, vector <double> d)
{
    for(int i = 0; i < 5; i++)
    {
        weights[i] -= d[i];
        weights[i] = clip(weights[i], 1, 5);
    }
}

void User::calc_estimation_weights()
{
    vector <double> weights = random_weights();
    vector <double> d(5);
    for(int t = 0; t < 1000; t++)
    {
        update_d(d);
        d = gradiant(ratings, weights);
        update_estimation_weights(weights, d);
    }
    estimation_weights = weights;
}

unsigned long int generate_hash(string password)
{
    return hash<string>()(password);
}