#ifndef WATER_HPP
#define WATER_HPP

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Water : public background {
  private:
    std::vector<std::string> s;

  public:
    void draw();
    void update();
    bool isFull();
    Water(int r, int c, int y, int x);
    ~Water();
};
#endif
