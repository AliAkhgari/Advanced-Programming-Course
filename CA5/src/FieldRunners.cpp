#include "FieldRunners.hpp"

using namespace std;

typedef SDL_FPoint Vector2D;
typedef Point Vector2D_Point;

void game()
{
    Window *window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    
    Player initial_player(20, 200);

    Player* player;
    player = &initial_player;
    
    FieldRunners fieldrunners(window, player);

    fieldrunners.make_random_enemies_order();
    
    int number = 0;

    while(true)
    {
        fieldrunners.show_background();

        player->show_player_details(window);

        fieldrunners.draw_path();
    
        fieldrunners.show_wave();

        if(fieldrunners.check_wave_ending(number) && fieldrunners.get_wave() < fieldrunners.get_wave_numbers())
        {
            fieldrunners.set_wave(fieldrunners.get_wave() + 1);
            fieldrunners.update_enemies();
        }
        if(fieldrunners.is_wave_finished() && fieldrunners.get_wave() == fieldrunners.get_wave_numbers())
        {
            fieldrunners.win();
            delay(3000);
            break;
        }
        
        for(int i = 0 ; i < fieldrunners.towers.size(); i++)
        {
            fieldrunners.towers[i].build_tower(window);
            if(fieldrunners.has_near_target(fieldrunners.towers[i].get_pos()))
                fieldrunners.send_bullets(&fieldrunners.towers[i]);
        }

        fieldrunners.is_wave_change = false;

        if(player->get_hearts() <= 0)
        {
            fieldrunners.lose();
            delay(3000);
            break;
        }

        fieldrunners.send_enemies(number);

        fieldrunners.update_window();

        delay(10);

        fieldrunners.update_frame();
    }
}

void FieldRunners::show_background()
{
    window->draw_img(BACKGROUND_IMG);
}

void FieldRunners::draw_path()
{
    for(int i = 0; i < enemy_path.size(); i++)
    {   
        if(i == enemy_path.size() - 1)
            window->fill_circle(float_to_int(enemy_path[i]), 10, RED);
        else
            window->fill_circle(float_to_int(enemy_path[i]), 10, WHITE);
    }
}

bool FieldRunners::is_wave_finished()
{
    if(wave_enemies.size() == 0)
        return true;

    return false;
}

void FieldRunners::send_enemies(int &number)
{
    for(int i = 0 ; i < number; i++)
    {
        wave_enemies[i].move(i);
        if(!wave_enemies[i].is_finished_the_path())
            wave_enemies[i].draw(window);

        if(wave_enemies[i].get_has_survived() == false)
        {
            player->deposit(wave_enemies[i].get_kill_reward());
            wave_enemies.erase(wave_enemies.begin() + i);
            number--;
        }

        if(wave_enemies[i].is_finished_the_path())
        {
            player->hearts_reduce(wave_enemies[i].get_survive_punishment());
            wave_enemies.erase(wave_enemies.begin() + i);
            number--;
        }
    }
    
    if(frame * 10 % ENTRANCE_DELAY == 0 && number < wave_enemies.size())
        number++;
}

bool FieldRunners::is_wave_ended(bool flag)
{
    int wave_numbers = file_numbers(WAVES_FILE).size()/4;
    if(is_wave_finished() && flag)
        return true;
    return false;
}

bool FieldRunners::check_wave_ending(int &number)
{
    static bool flag = true;
    int wave_numbers = file_numbers(WAVES_FILE).size()/4;
    if(is_wave_ended(flag))
    {
        set_frame(0);
        flag = false;
    }

    if(frame * 10 >= WAVE_DELAY && is_wave_finished())
    {
        flag = true;
        set_frame(0);
        number = 0;
        return true;
    }
    return false;
}

void FieldRunners::show_wave()
{
    string wave_message = "WAVE " + to_string(wave);
    window->show_text(wave_message, Point(650, 0), RED, FONT, 30);
}

vector <Enemy*> FieldRunners::targets_enemies(Point tower_pos)
{
    vector <Enemy*> targets;
    for(int i = 0; i < wave_enemies.size(); i++)
    {
        Vector2D_Point tower_to_enemy = vector2D(tower_pos, float_to_int(wave_enemies[i].get_pos()));
        if(vector2D_size(tower_to_enemy) <= SHOOTABLE_AREA &&
          !is_equal(wave_enemies[i].get_pos(), enemy_path[0]))
        {
            targets.push_back(&wave_enemies[i]);
        }
    }
    return targets;
}

bool FieldRunners::has_near_target(Point tower_pos)
{
    for(int i = 0; i < wave_enemies.size(); i++)
    {
        Vector2D_Point tower_to_enemy = vector2D(tower_pos, float_to_int(wave_enemies[i].get_pos()));
        if(vector2D_size(tower_to_enemy) <= SHOOTABLE_AREA &&
          !is_equal(wave_enemies[i].get_pos(), enemy_path[0]))
        {
            return true;
        }
    }
    return false;
}

Enemy* nearest_enemy(vector <Enemy*> targets, Point tower_pos)
{
    Enemy *nearest = targets[0];
    double min_size = vector2D_size(vector2D(int_to_float(tower_pos), nearest->get_pos()));
    for(int i = 1; i < targets.size(); i++)
    {
        if(vector2D_size(vector2D(int_to_float(tower_pos), targets[i]->get_pos())) < min_size)
        {
            min_size = vector2D_size(vector2D(int_to_float(tower_pos), targets[i]->get_pos()));
            nearest = targets[i];
        }
    }
    return nearest;
}

void FieldRunners::send_bullets(Tower* tower)
{
    static vector <Bullet> bullets;
    vector <Enemy*> targets;
    Enemy* target;
    
    targets = targets_enemies(tower->get_pos());

    
    if(targets.size())
        target = nearest_enemy(targets, tower->get_pos());

    if(frame * 10 % tower->get_shooting_delay() == 0)
    {
        Bullet bullet(tower->get_pos(), 200, target); 
        bullets.push_back(bullet);
    }
    if(is_wave_change == true)
    {
        bullets.clear();
        cout << "fuck u";
    }
    for(int i = 0; i < bullets.size(); i++)
    {
        bullets[i].move(tower);
        if(!bullets[i].get_is_reached())
            bullets[i].draw(window);
        else if(bullets[i].get_is_reached())
            bullets.erase(bullets.begin() + i);
        else if(bullets[i].get_target()->is_finished_the_path())
            bullets.erase(bullets.begin() + i);
        else if(!bullets[i].get_target()->get_has_survived())
            bullets.erase(bullets.begin() + i);
        else
            bullets.erase(bullets.begin() + i); 
    }
}

bool FieldRunners::is_valid_pos(Point pos)
{
    for(int i = 0; i < towers.size(); i++)
        if(is_equal(pos, towers[i].get_pos()))
            return false;

    for(int j = 0; j < enemy_path.size(); j++)
        if(is_equal(pos, nearest_house_center(float_to_int(enemy_path[j]))))
            return false;

    return true;
}

void FieldRunners::pressed_key(char key, Point pos)
{

    if(key == 'g' && player->get_money() >= GATTLING_BUILDING_COST)
    {
        Gattling gattling(pos, GATTLING1, GATTLING_DAMAGE, GATTLING_DELAY,
                    GATTLING_BUILDING_COST, GATTLING_UPGRADING_COST, GATTLING_UPGRADE_DAMAGE, Gattling_imgs);

        if(is_valid_pos(pos))
        {
            towers.push_back(gattling);
            player->money_reduce(GATTLING_BUILDING_COST);
        }
    }

    if(key == 'm' && player->get_money() >= MISSILE_BUILDING_COST)
    {
        Missile missile(pos, MISSILE1, MISSILE_DAMAGE, MISSILE_DELAY,
                    MISSILE_BUILDING_COST, MISSILE_UPGRADING_COST, MISSILE_UPGRADE_DAMAGE, Missile_imgs);
        
        if(is_valid_pos(pos))
        {
            towers.push_back(missile);
            player->money_reduce(MISSILE_BUILDING_COST);
        }
    }

    if(key == 't' && player->get_money() >= TESLA_BUILDING_COST)
    {
        Tesla tesla(pos, TESLA1, TESLA_DAMAGE, TESLA_DELAY,
                    TESLA_BUILDING_COST, TESLA_UPGRADING_COST, TESLA_UPGRADE_DAMAGE, Tesla_imgs);

        if(is_valid_pos(pos))
        {
            towers.push_back(tesla);
            player->money_reduce(TESLA_BUILDING_COST);
        }
    }

    if(key == 'u')
    {
        for(int i = 0; i < towers.size(); i++)
        {
            if(is_equal(pos, towers[i].get_pos()) &&
               player->get_money() >= towers[i].get_upgrade_cost() && towers[i].get_level() < 3)
            {
                   towers[i].upgrade_tower();
                   player->money_reduce(towers[i].get_upgrade_cost());
            }
        }
    }
}

void draw_rect(Window* window, Point pos)
{
    Point cell_pos = nearest_house_center(pos);
    
    window->draw_rect(Rectangle(cell_pos - Point(30, 30), cell_pos + Point(30, 30)));
}

void FieldRunners::update_window()
{
    static Point mouse_pos;
    static bool is_clicked = false;

    if(is_clicked)
        draw_rect(window, mouse_pos);
    
    window->update_screen();
    while(window->has_pending_event())
    {
        
        Event event = window->poll_for_event();
        char key;
        
        switch(event.get_type())
        {
            case Event::QUIT:
                exit(0);
                break;
            case Event::LCLICK:
                is_clicked = true;
                mouse_pos = get_current_mouse_position();
            
                break;
            case Event::KEY_PRESS:
                key = event.get_pressed_key();
                
                if(is_clicked)
                {
                    mouse_pos = nearest_house_center(mouse_pos);
                    pressed_key(key, mouse_pos);
                    is_clicked = false;
                }
                break;
        }
    }
}

void FieldRunners::lose()
{
    window->clear();
    show_background();
    window->show_text(LOSE_MESSAGE, Point(550, 400), RED, FONT, 60);
    update_window();
}

void FieldRunners::win()
{
    window->clear();
    show_background();
    window->show_text(WIN_MESSAGE, Point(550, 400), RED, FONT, 60);
    update_window();
}

void swap_order(Enemy &a, Enemy b)
{
    a = b;
}

void FieldRunners::make_random_enemies_order()
{
    vector <int> enemy_NO;
    while(enemy_NO.size() != wave_enemies.size())
    {
        srand(time(NULL));
        int random = rand() % wave_enemies.size();
        
        for(int i = 0; i < enemy_NO.size(); i++)
        {
            while(enemy_NO[i] == random)
            {
                random = rand() % wave_enemies.size();
                i = 0;
            }
        }
        enemy_NO.push_back(random);
    }
    for(int i = 0; i < enemy_NO.size(); i++)
        swap_order(wave_enemies[i], wave_enemies[enemy_NO[i]]);
}

