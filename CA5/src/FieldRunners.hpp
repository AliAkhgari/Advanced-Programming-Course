#ifndef FIELDRUNNERS_H
#define FIELDRUNNERS_H "FIELDRUNNERS_H"

#include <iostream>
#include <vector>
#include "rsdl.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "bullet.hpp"
#include "file.hpp"
#include "Player.hpp"
#include "Gattling.hpp"
#include "Tesla.hpp"
#include "missile.hpp"
#include "data.hpp"
#include <time.h>

#define WINDOW_NAME "Fieldrunners"
#define BACKGROUND_IMG "Assets/background.png"
#define WINDOW_WIDTH 1365 
#define WINDOW_HEIGHT 1024
#define ENTRANCE_DELAY 500
#define WAVE_DELAY 3000

#define GATTLING1 "Gattling"
#define GATTLING_DAMAGE 35
#define GATTLING_UPGRADE_DAMAGE 35
#define GATTLING_DELAY 1000
#define GATTLING_BUILDING_COST 55
#define GATTLING_UPGRADING_COST 40
#define GATTLING1_IMG "Assets/gattling1.png"
#define GATTLING2_IMG "Assets/gattling2.png"
#define GATTLING3_IMG "Assets/gattling3.png"

#define MISSILE1 "Missile"
#define MISSILE_DAMAGE 75
#define MISSILE_UPGRADE_DAMAGE 75
#define MISSILE_DELAY 3000
#define MISSILE_BUILDING_COST 70
#define MISSILE_UPGRADING_COST 60
#define MISSILE1_IMG "Assets/missile1.png"
#define MISSILE2_IMG "Assets/missile2.png"
#define MISSILE3_IMG "Assets/missile3.png"

#define TESLA1 "Tesla"
#define TESLA_DAMAGE 700
#define TESLA_UPGRADE_DAMAGE 1000
#define TESLA_DELAY 1500
#define TESLA_BUILDING_COST 120
#define TESLA_UPGRADING_COST 100
#define TESLA1_IMG "Assets/tesla1.png"
#define TESLA2_IMG "Assets/tesla2.png"
#define TESLA3_IMG "Assets/tesla3.png"

#define FONT "Assets/OpenSans.ttf"

#define WIN_MESSAGE "You Win!"
#define LOSE_MESSAGE "You Lose!"

#define SHOOTABLE_AREA 150

void game();

class FieldRunners
{
private:
    Window* window;

    int wave = 1;

    int frame = 0;

    int wave_numbers = file_numbers(WAVES_FILE).size()/4;

    std::vector <SDL_FPoint> enemy_path = enemy_direction();

    std::vector <int> enemy_numbers = file_numbers(WAVES_FILE);
    
    std::vector <std::string> Gattling_imgs = { GATTLING1_IMG, GATTLING2_IMG, GATTLING3_IMG };

    std::vector <std::string> Tesla_imgs = { TESLA1_IMG, TESLA2_IMG, TESLA3_IMG };

    std::vector <std::string> Missile_imgs = { MISSILE1_IMG, MISSILE2_IMG, MISSILE3_IMG };
    
    Player* player;

public:
    FieldRunners(Window* window_, Player* player_)
    {
        window = window_;
        player = player_;
    }

    std::vector <Enemy> wave_enemies = enemies_info(wave);

    std::vector <Tower> towers;
    
    void update_enemies () { is_wave_change = true; wave_enemies = enemies_info(wave); make_random_enemies_order(); }

    void update_frame () { frame++; }

    void draw_path();

    void send_enemies(int &number);

    void show_background();

    void update_window();

    void show_enemy_path();

    bool is_wave_change = false;

    void pressed_key(char key, Point pos);

    bool is_wave_finished();

    bool is_wave_ended(bool flag);

    bool check_wave_ending(int &number);

    void show_wave();

    std::vector <Enemy*> targets_enemies(Point tower_pos);

    bool has_near_target(Point tower_pos);

    void send_bullets(Tower* tower);

    void check_player_details ();

    bool is_valid_pos(Point pos);
    
    void make_random_enemies_order();

    void lose ();

    void win ();

    int get_wave () { return wave; }

    int get_wave_numbers () { return wave_numbers; }
    
    void set_wave (int number) { wave = number; }

    int get_frame () { return frame; }

    void set_frame (int value) { frame = value; }

};




#endif