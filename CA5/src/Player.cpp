#include "Player.hpp"
#include <vector>
#include <string>

#define FONT "Assets/OpenSans.ttf"

using namespace std;

Player::Player(int hearts_, int money_)
{
    money = money_;
    hearts = hearts_;
}

void Player::show_player_details(Window* window)
{
    string hearts_message = "Hearts : " + to_string(hearts);
    string money_message = "Money : " + to_string(money);
    Point src(50, 50);
    window->show_text(hearts_message, src, WHITE, FONT, 24);
    window->show_text(money_message, src + Point(300, 0), WHITE, FONT, 24);
}

void Player::money_reduce(int amount)
{
    money -= amount;
}

void Player::deposit(int amount)
{
    money += amount;
}

void Player::hearts_reduce(int amount)
{
    hearts -= amount;
}