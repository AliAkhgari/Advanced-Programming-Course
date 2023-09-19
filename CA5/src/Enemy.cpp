#include "Enemy.hpp"

using namespace std;

Enemy::Enemy(SDL_FPoint current_position_,string type_, float health_, float velocity_, int kill_reward_, int survive_punishment_,
             int wave_number_, bool is_ended_, bool has_survived_, string img_, Point img_size_, float max_health_)//, SDL_FPoint current_position_)
{
    current_position = current_position_;
    type = type_;
    health = health_;
    velocity = velocity_;
    kill_reward = kill_reward_;
    survive_punishment = survive_punishment_;
    wave_number = wave_number_;
    is_ended = is_ended_;
    has_survived = has_survived_;
    img = img_;
    img_size = img_size_;
    max_health = max_health_;
}

void Enemy::move(int num)
{
    static vector <int> states(100);

    vector <SDL_FPoint> path = enemy_direction();

    if(is_equal(current_position, path[states[num] + 1]))
        states[num]++;

    SDL_FPoint src = path[states[num]];
    SDL_FPoint dst = path[states[num]+1];

    src_to_dst = vector2D(src, dst);

    if(!has_survived)
        states.erase(states.begin() + num);
    if(!is_equal(current_position, path[path.size() - 1]))
    {
        if(src_to_dst.x < 0)
            current_position.x -= velocity / 100;
        if(src_to_dst.x > 0)
            current_position.x += velocity / 100;
        if(src_to_dst.y > 0)
            current_position.y += velocity / 100;
        if(src_to_dst.y < 0)
            current_position.y -= velocity / 100; 
    }
    else
    {
        states.erase(states.begin() + num);
        is_ended = true;
    }
}

void Enemy::draw(Window* window)
{
    SDL_FPoint Img_size = int_to_float(img_size);
    Point top_left = float_to_int(operator-(current_position, Img_size));
    Point bottom_right = float_to_int(operator+(current_position, Img_size));
    window->draw_img(img, Rectangle(top_left, bottom_right));
    window->fill_rect(Rectangle(float_to_int(current_position) - Point(30, 50), 50, 4), GREEN);
    window->fill_rect(Rectangle(float_to_int(current_position) - Point(30, 50),50 - health/max_health * 100/2, 4), RED);
}

void Enemy::damaged(int amount)
{
    health -= amount;
    if(health <= 0)
        has_survived = false;
}
