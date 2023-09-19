#ifndef PLAYER_H
#define PLAYER_H "PLAYER_H"

#include "file.hpp"
#include "rsdl.hpp"

class Player
{
private:
    int hearts;
    int money;
public:
    Player(int hearts_, int money_);
    
    void show_player_details(Window* window);

    int get_money () { return money; }

    void money_reduce(int amount);

    void deposit(int amount);

    void hearts_reduce(int amount);

    int get_hearts() { return hearts; }

};

#endif