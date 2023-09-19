#ifndef TOWER_H
#define TOWER_H "TOWER_H"

#include "file.hpp"
#include "rsdl.hpp"
#include "Enemy.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Tower
{
protected:
    Point position;
    std::string type;
    int level = 1;
    int damage;
    int shooting_delay;
    int buliding_cost;
    int upgrading_cost;
    int upgrading_damage;
    std::vector <std::string> img;
public:
    Tower(Point position_, std::string type_, int damage_,
          int shooting_delay_, int buliding_cost_, 
          int upgrading_cost_, int upgrading_damage_, std::vector <std::string> img_);

    void build_tower(Window* window);

    void calculate_damage();

    void upgrade_tower ();
    
    Point get_pos () { return position; }

    std::string get_kind () { return type; }

    int get_upgrade_cost () { return upgrading_cost; }

    int get_shooting_delay () { return shooting_delay; }

    int get_damage() { return damage; }

    int get_level () { return level; }
};






#endif