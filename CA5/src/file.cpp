#include "file.hpp"

using namespace std;

string file_content(string file_name)
{
    ifstream input_file(file_name);
    stringstream file_content;
    file_content << input_file.rdbuf();
    return file_content.str();
}

vector <int> first_line_of_file(string file_name)
{
    string file = file_content(file_name);
    stringstream file_data(file);
    vector <int> data;
    string number;
    string line;
    while(getline(file_data, line, '\n'))
    {
        stringstream line_data(line);
        line_data >> number;
        while(line_data)
        {
            data.push_back(stoi(number));
            line_data >> number;
        }
        break;
    }
    return data;
}

vector <int> file_numbers(string file_name)
{
    string file = file_content(file_name);
    stringstream file_data(file);
    file_data.ignore(numeric_limits <streamsize>::max(),'\n');
    vector <int> data;
    string number;
    string line;
    while(getline(file_data, line, '\n'))
    {
        stringstream line_data(line);
        line_data >> number;
        while(line_data)
        {
            data.push_back(stoi(number));
            line_data >> number;
        }
    }
    return data;
}

vector <pair <int, int> > cells_position()
{
    vector <int> first_line = first_line_of_file(WAVES_FILE);
    vector <pair <int, int> > cells_pos;
    for(int i = 0; i < first_line.size(); i+=2)
    {
        cells_pos.push_back(make_pair(first_line[i], first_line[i + 1]));
    }
    for(int i = 0; i <cells_pos.size() - 1; i++)
    {
        if(cells_pos[i + 1].first - cells_pos[i].first > 1)
            cells_pos.insert(cells_pos.begin() + i + 1, make_pair(cells_pos[i].first + 1, cells_pos[i].second));
        if(cells_pos[i + 1].second - cells_pos[i].second > 1)
            cells_pos.insert(cells_pos.begin() + i + 1, make_pair(cells_pos[i].first, cells_pos[i].second + 1));
        if(cells_pos[i + 1].first - cells_pos[i].first < -1)
            cells_pos.insert(cells_pos.begin() + i + 1, make_pair(cells_pos[i].first - 1, cells_pos[i].second));
        if(cells_pos[i + 1].second - cells_pos[i].second < -1)
            cells_pos.insert(cells_pos.begin() + i + 1, make_pair(cells_pos[i].first, cells_pos[i].second - 1));
    }
    return cells_pos;
}

vector <SDL_FPoint> enemy_direction()
{
    vector <pair <int, int> > cells_pos = cells_position();
    vector <SDL_FPoint> enemy_path;
    SDL_FPoint SDL_FPoint;
    for(int i = 0; i < cells_pos.size(); i++)
    {
        SDL_FPoint.x = cells_pos[i].first * 60 + 150;
        SDL_FPoint.y = cells_pos[i].second  * 60 + 205;
        enemy_path.push_back(SDL_FPoint);
    }
    return enemy_path;
}

vector <Point> cells_center()
{
    vector <Point> center_of_cells;
    for(int i = 0; i < 19; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            center_of_cells.push_back(Point(150 + i * 60, 205 + j * 60));
        }
    }
    return center_of_cells;
}

SDL_FPoint operator+(SDL_FPoint a, SDL_FPoint b)
{
    SDL_FPoint output;
    output.x = roundf((a.x + b.x) * 10) / 10;
    output.y = roundf((a.y + b.y) * 10) / 10;
    return output;
}

SDL_FPoint operator-(SDL_FPoint a, SDL_FPoint b)
{
    SDL_FPoint output;
    output.x = roundf((a.x - b.x) * 10) / 10;
    output.y = roundf((a.y - b.y) * 10) / 10;
    return output;
}

SDL_FPoint operator*(SDL_FPoint a, float c)
{
    SDL_FPoint output;
    output.x = a.x * c;
    output.y = a.y * c;
    return output;
}

SDL_FPoint operator/(SDL_FPoint a, float c)
{
    SDL_FPoint output;
    output.x = a.x / c;
    output.y = a.y / c;
    return output;
}

void appointment_operator(SDL_FPoint &a, SDL_FPoint b)
{
    a.x = b.x;
    a.y = b.y;
}

SDL_FPoint vector2D(SDL_FPoint src, SDL_FPoint dst)
{
    return operator-(dst, src);
}

Point vector2D(Point src, Point dst)
{
    return dst.operator-(src);
}

double vector2D_size(SDL_FPoint vector2D)
{
    return sqrt( pow(vector2D.x, 2) + pow(vector2D.y, 2) );
}

double vector2D_size(Point vector2D)
{
    return sqrt( pow(vector2D.x, 2) + pow(vector2D.y, 2) );
}

bool is_equal(SDL_FPoint a, SDL_FPoint b)
{
    if((a.x) == (b.x) && (a.y) == (b.y))
        return true;
    return false;
}

bool is_equal(Point a, Point b)
{
    if((a.x) == (b.x) && (a.y) == (b.y))
        return true;
    return false;
}

bool is_bigger(SDL_FPoint a, SDL_FPoint b)
{
    if(a.x >= b.x && a.y >= b.y)
        return true;
    return false;
}

Point float_to_int(SDL_FPoint input)
{
    Point output;
    output.x = (int)input.x;
    output.y = (int)input.y;
    return output;
}

SDL_FPoint int_to_float(Point input)
{
    SDL_FPoint output;
    output.x = (float)input.x;
    output.y = (float)input.y;
    return output;
}

Vector2D calculate_velocity(Vector2D src_to_dst, int speed)
{
    Vector2D velocity;
    velocity.x = 0;
    velocity.y = 0;
    if(src_to_dst.x != 0)
        velocity.x = speed * 0.01;
    if(src_to_dst.y != 0)
        velocity.y = speed * 0.01;
    
    return velocity;
}

Point nearest_house_center(Point pos)
{
    vector <Point> houses_center = cells_center();
    Point nearest;
    double min_size = vector2D_size(vector2D(pos, houses_center[0]));
    for(int i = 1; i < houses_center.size(); i++)
    {
        if(min_size > vector2D_size(vector2D(pos, houses_center[i])))
            min_size = vector2D_size(vector2D(pos, houses_center[i]));
    }

    for(int i = 0; i < houses_center.size(); i++)
    {
        if(min_size == vector2D_size(vector2D(pos, houses_center[i])))
        {
            nearest = houses_center[i];
            break;
        }
    }
    return nearest;
}