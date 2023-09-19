#include "CSVReader.hpp"
#include "UTRIP.hpp"
#include "GET.hpp"
#include "POST.hpp"
#include "DELETE.hpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

typedef vector <pair <int, vector <string> > > Hotels;

vector <string> commands(string line);
bool is_not_command(string input);

int main(int argc, char const *argv[])
{
    CSVReader csv_reader(argv[1]);
    Hotels hotels_information = csv_reader.get_rows_information();
    UTRIP* utrip = new UTRIP(hotels_information);
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
