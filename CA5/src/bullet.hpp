#ifndef BULLET_H
#define BULLET_H "BULLET_H"

#include "rsdl.hpp"
#include "file.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include <vector>
#include <iostream>

typedef SDL_FPoint Vector2D;

class Bullet
{
private:
    SDL_FPoint current_position;
    Enemy* target;
    std::string img;
    int speed;  
    bool has_been_hit = false;
public:
    Bullet(Point current_position_, int speed_, Enemy* target_);

    void move (Tower* tower);

    void draw(Window *window);

    bool get_is_reached () { return has_been_hit; }

    Enemy* get_target () { return target; }
};


#endif