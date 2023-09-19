#ifndef ENEMY_H
#define ENEMY_H "ENEMY_H"

#include "rsdl.hpp"
#include "file.hpp"
#include "data.hpp"
#include <vector>
#include <string>
#include <sstream>

typedef SDL_FPoint Vector2D;

class Enemy
{
private:
    SDL_FPoint current_position;
    std::string type;
    float health;
    float velocity;
    int kill_reward;
    int survive_punishment;
    int wave_number;
    bool has_survived;
    bool is_ended;
    std::string img;
    Point img_size;
    float max_health;
    
public:
    Vector2D src_to_dst;
    
    Enemy(SDL_FPoint current_position_, std::string type_, float health_, float velocity_, int kill_reward_,
          int survive_punishment_, int wave_number_,
          bool is_ended_, bool has_survived_, std::string img_, Point img_size_, float max_health_);

    void move(int num);
    
    void draw(Window* window);

    SDL_FPoint get_pos () { return current_position; }

    bool get_has_survived () { return has_survived; }

    bool is_finished_the_path () { return is_ended; }

    std::string get_kind () { return type; }

    void damaged(int amount);

    int get_survive_punishment () { return survive_punishment; }

    int get_kill_reward () { return kill_reward; }
};

#endif