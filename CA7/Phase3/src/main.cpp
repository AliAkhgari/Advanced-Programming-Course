#include "CSVReader.hpp"
#include "UTRIP.hpp"
#include "GET.hpp"
#include "POST.hpp"
#include "DELETE.hpp"
#include "my_server.hpp"
#include "handlers.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

typedef vector <pair <int, vector <string> > > Rows;

int main(int argc, char **argv)
{
    CSVReader hotels_csv(argv[1]);
    CSVReader ratings_csv(argv[2]);
    Rows hotels_information = hotels_csv.get_rows_information();
    Rows ratings_information = ratings_csv.get_rows_information();
    UTRIP* utrip = new UTRIP(hotels_information);
    utrip->set_ratings(ratings_information);

    try 
    {
        MyServer server(8080);
        server.setNotFoundErrPage("static/404.html");
        server.get("/", new ShowPage("static/mainpage.html"));
        server.get("/signup", new ShowPage("static/signupcss.html"));
        server.post("/signup", new SignupHandler(utrip));
        server.get("/login", new ShowPage("static/logincss.html"));
        server.post("/login", new LoginHandler(utrip));
        server.get("/hotelDetails", new HotelDetailsHandler(utrip));
        server.get("/exit", new LogoutHandler(utrip));
        server.get("/home", new HomeHandler(utrip));
        server.post("/filter", new FilterHandler(utrip));
        server.get("/account", new EditAccount(utrip));
        server.post("/updateAccount", new UpdateAccount(utrip));
        server.run();
    } 
    catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }    
















    // string line;
    // while (getline(cin, line))
    // {
    //     vector <string> orders = commands(line);
    //     string main_command = orders[0];

    //     if(main_command == GET_COMMAND)
    //     {
    //         GET* new_get = new GET(utrip, orders);
    //         try {
    //             new_get->read_command();
    //         } catch(const std::exception& e) {
    //             cout << e.what() << '\n';
    //         }
    //         delete new_get;
    //     }
    //     else if(main_command == POST_COMMAND)
    //     {
    //         POST* new_post = new POST(utrip, orders);
    //         try {
    //             new_post->read_command();
    //         } catch(const std::exception& e) {
    //             cout << e.what() << '\n';
    //         }
    //         delete new_post;
    //     }
    //     else if(main_command == DELETE_COMMAND)
    //     {
    //         DELETE* new_delete = new DELETE(utrip, orders);
    //         try {
    //             new_delete->read_command();
    //         } catch(const std::exception& e) {
    //             cout << e.what() << '\n';
    //         }            
    //         delete new_delete;
    //     }
    //     else
    //         cout << BAD_REQUEST_ERROR << endl;
    // }
    // return 0;
}
