#include "bullet.hpp"

using namespace std;

Bullet::Bullet(Point current_position_, int speed_, Enemy* target_)
{
    current_position = int_to_float(current_position_);
    speed = speed_;
    target = target_;
}

void Bullet::move(Tower* tower)
{
    SDL_FPoint src = int_to_float(tower->get_pos());
    SDL_FPoint dst;
    dst.x = target->get_pos().x;
    dst.y = target->get_pos().y;
    Vector2D src_to_dst = vector2D(current_position, dst);

    if(vector2D_size(vector2D(current_position, dst)) > 5)
    {
        if(src_to_dst.x < 0)
            current_position.x -= speed / 100;
        if(src_to_dst.x > 0)
            current_position.x += speed / 100;
        if(src_to_dst.y > 0)
            current_position.y += speed / 100;
        if(src_to_dst.y < 0)
            current_position.y -= speed / 100;
    }
    else
    {
        if(target->get_kind() != "StubbornRunner" || tower->get_kind() != "Gattling")
            target->damaged(tower->get_damage());
            
        has_been_hit = true;
    }
}

void Bullet::draw(Window *window)
{
    window->fill_circle(float_to_int(current_position), 5, RED);
}


  