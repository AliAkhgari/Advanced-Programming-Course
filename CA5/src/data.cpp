#include "data.hpp"

using namespace std;

vector <Enemy> enemies_info(int wave)
{
    vector <Enemy> enemies;

    vector <SDL_FPoint> enemy_path = enemy_direction();

    vector <int> enemy_numbers = file_numbers(WAVES_FILE);

    vector <string> enemy_kind = { RUNNER, STUBBORN_RUNNER, SUPER_TROOPER, SCRAMBLER };

    vector <string> img_direction = { RUNNER_IMG, STUBBORN_RUNNER_IMG,
                                                SUPER_TROOPER_IMG, SCRAMBLER_IMG };

    vector <float> enemies_health = { RUNNER_HEALTH, STUBBORN_RUNNER_HEALTH,
                                         SUPER_TROOPER_HEALTH, SCRAMBLER_HEALTH };

    vector <float> enemies_speed = { RUNNER_SPEED, STUBBORN_RUNNER_SPEED,
                                          SUPER_TROOPER_SPEED, SCRAMBLER_SPEED };

    vector <int> enemies_kill_reward = { RUNNER_KILL_REWARD, STUBBORN_RUNNER_KILL_REWARD,
                                              SUPER_TROOPER_KILL_REWARD, SCRAMBLER_KILL_REWARD };

    vector <int> enemies_survive_punishment = { RUNNER_SURVIVE_PUNISHMENT,
                                                     STUBBORN_RUNNER_SURVIVE_PUNISHMENT,
                                                     SUPER_TROOPER_SURVIVE_PUNISHMENT,
                                                     SCRAMBLER_SURVIVE_PUNISHMENT };

    vector <Point> imgs_size = {Point(RUNNER_IMG_WIDTH, RUNNER_IMG_HEIGHT), 
                                     Point(STUBBORN_RUNNER_IMG_WIDTH, STUBBORN_RUNNER_IMG_HEIGHT), 
                                     Point(SUPER_TROOPER_IMG_WIDTH, SUPER_TROOPER_IMG_HEIGHT),
                                     Point(SCRAMBLER_IMG_WIDTH, SCRAMBLER_IMG_HEIGHT) };

    SDL_FPoint default_point;
    default_point.x = 0;
    default_point.y = 0;
    for(int i = (wave - 1) * 4; i < wave * 4; i++)
    {
        for(int j = 0; j < enemy_numbers[i]; j++)
        {
            enemies.push_back( Enemy(enemy_path[0], enemy_kind[i%4], (0.9 + 0.1 * (float)wave) * enemies_health[i%4], enemies_speed[i%4],
            enemies_kill_reward[i%4], enemies_survive_punishment[i%4], wave,
            false, true, img_direction[i%4], imgs_size[i%4], (0.9 + 0.1 * (float)wave) * enemies_health[i%4]));
        }
    }
    return enemies;
}

