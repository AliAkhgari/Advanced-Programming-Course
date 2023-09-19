#include "CSVReader.hpp"
#include "UTRIP.hpp"
#include "GET.hpp"
#include "POST.hpp"
#include "DELETE.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

typedef vector <pair <int, vector <string> > > Rows;

vector <string> commands(string line);

int main(int argc, char const *argv[])
{
    CSVReader hotels_csv(argv[1]);
    CSVReader ratings_csv(argv[2]);
    Rows hotels_information = hotels_csv.get_rows_information();
    Rows ratings_information = ratings_csv.get_rows_information();

    UTRIP* utrip = new UTRIP(hotels_information);
    utrip->set_ratings(ratings_information);

    string line;
    while (getline(cin, line))
    {
        vector <string> orders = commands(line);
        string main_command = orders[0];

        if(main_command == GET_COMMAND)
        {
            GET* new_get = new GET(utrip, orders);
            try {
                new_get->read_command();
            } catch(const std::exception& e) {
                cout << e.what() << '\n';
            }
            delete new_get;
        }
        else if(main_command == POST_COMMAND)
        {
            POST* new_post = new POST(utrip, orders);
            try {
                new_post->read_command();
            } catch(const std::exception& e) {
                cout << e.what() << '\n';
            }
            delete new_post;
        }
        else if(main_command == DELETE_COMMAND)
        {
            DELETE* new_delete = new DELETE(utrip, orders);
            try {
                new_delete->read_command();
            } catch(const std::exception& e) {
                cout << e.what() << '\n';
            }            
            delete new_delete;
        }
        else
            cout << BAD_REQUEST_ERROR << endl;
    }
    return 0;
}

vector <string> commands(string line)
{
    vector <string> orders;
    stringstream command(line);
    string info;
    while(command)
    {
        command >> info;
        orders.push_back(info);
    }
    orders.pop_back();
    return orders;
}
