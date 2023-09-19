#include "Tower.hpp"

using namespace std;

class Bullet;

typedef SDL_FPoint Vector2D;


Tower::Tower(Point position_,string type_, int damage_, int shooting_delay_,
             int buliding_cost_, int upgrading_cost_, int upgrading_damage_, vector <string> img_) 
{
    position = position_;
    type = type_;
    damage = damage_;
    shooting_delay = shooting_delay_;
    buliding_cost = buliding_cost_;
    upgrading_cost = upgrading_cost_;
    upgrading_damage = upgrading_damage_;
    img = img_;
}

void Tower::build_tower(Window* window)
{
    Point f;
    f.x = 50;
    f.y = 50;
    Point top_left = position.operator-(f);
    Point bottom_right = position.operator+(f);
    window->draw_img(img[level - 1], Rectangle(top_left, bottom_right));
} 

void Tower::upgrade_tower()
{
    level++;
    damage += upgrading_damage;
}