#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Building : public background {
  private:
    std::string s[8];

  public:
    void draw();
    void update();
    bool isFull(){};
    Building(int y, int x);
    ~Building();
};
#endif
