#ifndef FILE_H
#define FILE_H "FILE_H"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ostream>
#include <sstream>
#include <cmath>
#include "rsdl.hpp"

#define WAVES_FILE "wave.txt"

typedef SDL_FPoint Vector2D;

std::string file_content(std::string file_name);
std::vector <int> first_line_of_file(std::string file_name);
std::vector <int> file_numbers(std::string file_name);
std::vector <std::pair <int, int> > cells_position();
std::vector <SDL_FPoint> enemy_direction();
std::vector <Point> cells_center();

SDL_FPoint operator+(SDL_FPoint a, SDL_FPoint b);
SDL_FPoint operator-(SDL_FPoint a, SDL_FPoint b);
SDL_FPoint operator*(SDL_FPoint a, float c);
SDL_FPoint operator/(SDL_FPoint a, float c);
void appointment_operator(SDL_FPoint &a, SDL_FPoint b);
SDL_FPoint vector2D(SDL_FPoint src, SDL_FPoint dst);
Point vector2D(Point src, Point dst);
double vector2D_size(Point vector2D);
double vector2D_size(SDL_FPoint vector2D);
bool is_equal(SDL_FPoint a, SDL_FPoint b);
bool is_equal(Point a, Point b);
bool is_bigger(SDL_FPoint a, SDL_FPoint b);
Point float_to_int(SDL_FPoint input);
SDL_FPoint int_to_float(Point input);
Vector2D calculate_velocity(Vector2D src_to_dst, int speed);
Point nearest_house_center(Point pos);

#endif