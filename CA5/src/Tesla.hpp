#ifndef TESLA_H
#define TESLA_H "TESLA_H"

#include "Tower.hpp"
#include <vector>
#include <string>

class Tesla : public Tower
{
private:
  
public:
    Tesla(Point position_, std::string type_, int damage_,
          int shooting_delay_, int buliding_cost_, int upgrading_cost_, int upgrading_damage_, std::vector <std::string> img_)
        : Tower(position_, type_, damage_, shooting_delay_, buliding_cost_, upgrading_cost_, upgrading_damage_, img_)
        {
            
        }

    void upgrade();
};



#endif
