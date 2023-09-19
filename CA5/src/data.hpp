#ifndef DATA_H
#define DATA_H "DATA_H"

#include "Enemy.hpp"
#include <vector>
#include <string>

class Enemy;

#define WAVES_FILE "wave.txt"
#define RUNNER "Runner"
#define RUNNER_HEALTH 250
#define RUNNER_SPEED 50
#define RUNNER_KILL_REWARD 6
#define RUNNER_SURVIVE_PUNISHMENT 1
#define RUNNER_IMG "Assets/runner.png"
#define RUNNER_IMG_WIDTH 30
#define RUNNER_IMG_HEIGHT 40


#define STUBBORN_RUNNER "StubbornRunner"
#define STUBBORN_RUNNER_HEALTH 400
#define STUBBORN_RUNNER_SPEED 25
#define STUBBORN_RUNNER_KILL_REWARD 10
#define STUBBORN_RUNNER_SURVIVE_PUNISHMENT 4
#define STUBBORN_RUNNER_IMG "Assets/stubborn-runner.png" 
#define STUBBORN_RUNNER_IMG_WIDTH 30
#define STUBBORN_RUNNER_IMG_HEIGHT 40

#define SUPER_TROOPER "SuperTrooper"
#define SUPER_TROOPER_HEALTH 500
#define SUPER_TROOPER_SPEED 25
#define SUPER_TROOPER_KILL_REWARD 8
#define SUPER_TROOPER_SURVIVE_PUNISHMENT 4
#define SUPER_TROOPER_IMG "Assets/supertrooper.png"
#define SUPER_TROOPER_IMG_WIDTH 30
#define SUPER_TROOPER_IMG_HEIGHT 40

#define SCRAMBLER "Scrambler"
#define SCRAMBLER_HEALTH 100
#define SCRAMBLER_SPEED 100
#define SCRAMBLER_KILL_REWARD 4
#define SCRAMBLER_SURVIVE_PUNISHMENT 2
#define SCRAMBLER_IMG "Assets/scrambler.png"
#define SCRAMBLER_IMG_WIDTH 40
#define SCRAMBLER_IMG_HEIGHT 40


std::vector <Enemy> enemies_info(int wave);


#endif