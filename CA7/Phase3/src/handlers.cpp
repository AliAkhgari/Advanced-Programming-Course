#include "handlers.hpp"

using namespace std;

bool is_have(vector <string> inputs, string input)
{
  for(int i = 0; i < inputs.size(); i++)
    if(inputs[i] == input)
      return true;
  
  return false;
}

Response *SignupHandler::callback(Request *req) 
{
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string re_password = req->getBodyParam("re_password");
  string email = req->getBodyParam("email");
  if(re_password != password)
    throw Server::Exception("Passwords are not same!");

  utrip->sign_up(username, email, password);
  Response *res = Response::redirect("/");
  res->setSessionId(email);
  utrip->session_ids.push_back(email);

  return res;
}

Response *LoginHandler::callback(Request *req) 
{
  string email = req->getBodyParam("email");
  string password = req->getBodyParam("password");
  utrip->login(email, password);
  Response *res = Response::redirect("/");
  res->setSessionId(email);
  utrip->session_ids.push_back(email);
  return res;
}

Response *LogoutHandler::callback(Request *req)
{
  Response *res = new Response;
  if(!is_have(utrip->session_ids, req->getSessionId()))
  {
    res = Response::redirect("/login");
    return res;
  }
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body
  << "<!DOCTYPE html>"
  << "<html>"
  << "<body style='text-align: center;'>"
  << "<h2>"
  << req->getSessionId() << " logged out!"
  << "</h2>"
  << "</body>"
  << "</html>";
  res->setBody(body.str());
  utrip->logout();

  res = Response::redirect("/login");
  res->setSessionId("");

  return res;
}

Response *HomeHandler::callback(Request *req) 
{
  Response *res = new Response;
  if(!is_have(utrip->session_ids, req->getSessionId()))
  {
    res = Response::redirect("/login");
    return res;
  }
  res->setHeader("Content-Type", "text/html");
  vector <Hotel*> hotels = utrip->get_hotels();
  ostringstream body;
  body
  << "<!DOCTYPE html>"
  << "<html>"
  << "<body style='text-align: center;'>"
  << "<h1>UTRIP</h1>"
  << "<div class='topnav'>"
  << "<table border='1' text-align='center' style='width:100%'>"
  << "<td><a href='/home'>Home</a></td>"
  << "<td><a href='/signup'>Signup</a></td>"
  << "<td><a href='/login'>Login</a></td>"
  << "<td><a href='/account'>Account</a></td>"
  << "<td><a href='/exit'>Exit</a></td>"
  << "</table>"
  << "</div>"
  << "<br> <br>"
  << "<form action='/filter' method='post'>"
  << "<input name='min_star' type='text' placeholder='Min Star' style='display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;' />"
  << "<input name='max_star' type='text' placeholder='Max Star' style='display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;' />"
  << "<button type='submit' style='display:block; width: 100%; padding: 7px;'>Submit</button>"
  << "</form>";
  for(int i = 0; i < hotels.size(); i++)
  {
    string image_url = "\"" + hotels[i]->get_image_url() + "\"";
    string image_html_link = "<img src=" + image_url + "width='500' height='333'>";
    body
    << "<h2><a href='/hotelDetails?id=" << hotels[i]->get_id() << "'>" << hotels[i]->get_name() << "</a></h2>"
    << "<h3>"
    << "Star : "
    << hotels[i]->get_star()
    << "<br>"
    << "City : "
    << hotels[i]->get_city()
    << "<br>"
    << image_html_link
    << "<br>";
  }
  body
  << "</h3>"
  << "</body>"
  << "</html>";
  res->setBody(body.str());
  return res;
}

Response *FilterHandler::callback(Request *req) 
{
  utrip->filter_star(stoi(req->getBodyParam("min_star")), stoi(req->getBodyParam("max_star")));
  return Response::redirect("/home");
}


Response *EditAccount::callback(Request *req)
{
  Response *res = new Response;
  if(!is_have(utrip->session_ids, req->getSessionId()))
  {
    res = Response::redirect("/login");
    return res;
  }
  res->setHeader("Content-Type", "text/html");
  User* user = utrip->get_logged_in_user();
  ostringstream body;
  body
    << "<html>"
    << "<head><title>Account</title></head>"
    << "<br><h1>UTRIP</h1>"
    << "<body style='text-align: center;'>"
    << "<p>"
    << "<div class='topnav'>"
    << "<table border='1' text-align='center' style='width:100%'>"
    << "<td><a href='/home'>Home</a></td>"
    << "<td><a href='/signup'>Signup</a></td>"
    << "<td><a href='/login'>Login</a></td>"
    << "<td><a href='/account'>Account</a></td>"
    << "<td><a href='/exit'>Exit</a></td>"
    << "</table>"
    << "</div>"
    << "<br> <br>"
    << "<h2> Account : " << user->get_user_name() << "</h2><br>"
    << "<h2> Current balance : " << user->get_balance() << "</h2><br>"
    << "</p>"
    << "<form action='updateAccount' method='POST'>"
    << "<input type='hidden' name='id' value='" << user->get_user_name() << "'/>"
    << "<h2> Amount: <input type='text' name='amount' value='" << "'/> </h2>"
    << "<input type='submit' value='Save'/>"
    << "</form>"
    << "</body>"
    << "</html>";

  res->setBody(body.str());
  return res;
}

Response *UpdateAccount::callback(Request *req) 
{
  utrip->get_logged_in_user()->increase_balance(stod(req->getBodyParam("amount")));
  return Response::redirect("/account");
}

vector <string> property_list(string properties)
{
  vector <string> property_amenities;
  stringstream property_ss(properties);
  string property;
  while(getline(property_ss, property, '|'))
  {
    property_amenities.push_back(property);
  }
  return property_amenities;
}

Response *HotelDetailsHandler::callback(Request *req)
{
  Response *res = new Response;
  if(!is_have(utrip->session_ids, req->getSessionId()))
  {
    res = Response::redirect("/login");
    return res;
  }
  res->setHeader("Content-Type", "text/html");
  Hotel* hotel = utrip->find_hotel_by_id(req->getQueryParam("id"));
  vector <string> properties = property_list(hotel->get_property());
  string image_url = "\"" + hotel->get_image_url() + "\"";
  string image_html_link = "<img src=" + image_url + "width='500' height='333'>";
  ostringstream body;
  body
  << "<html>" << endl
  << "<head><title>Hotel Details</title></head>" << endl
  << "<body>"
  << "<h2>" << hotel->get_name() << "</h2>"
  << image_html_link
  << "<br>"
  << "<p>"
  << "<h3>" << "Overview" << "</h3>" << hotel->get_overview() << "<br>"
  << "<h3>" << "Property Amenities"  << "</h3>";
  for(int i = 0; i < properties.size(); i++)
    body << "<ul>" << "<li>" << properties[i] << "</li> </ul>\n";

  body
  << "<h3>" << "Star Rating : " << hotel->get_star() << "</h3>"
  << "<h3>" << "City : " << hotel->get_city() << "</h3>"
  << "<table border=1 text-align=center style='width:100%'>"
  << "<tr>"
  << "<th>  </th>"
  << "<th>Standard Room</th>"
  << "<th>Deluxe Room</th> "
  << "<th>Luxury Room</th>"
  << "<th>Premium Room</th>"
  << "</tr>"
  << "<tr>"
  << "<td>Price</td>"
  << "<td>" << hotel->get_rooms_info().standard_room_price << "</td>"
  << "<td>" << hotel->get_rooms_info().deluxe_room_price << "</td>"
  << "<td>" << hotel->get_rooms_info().luxury_room_price << "</td>"
  << "<td>" << hotel->get_rooms_info().premium_room_price << "</td>"
  << "</tr>"
  << "<tr>"
  << "<td>Number</td>"
  << "<td>" << hotel->get_rooms_info().num_of_standard_rooms << "</td>"
  << "<td>" << hotel->get_rooms_info().num_of_deluxe_rooms << "</td>"
  << "<td>" << hotel->get_rooms_info().num_of_luxury_rooms << "</td>"
  << "<td>" << hotel->get_rooms_info().num_of_premium_rooms << "</td>"
  << "</tr>"
  << "</table>" 
  << "</p>"
  << "</body>"
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}