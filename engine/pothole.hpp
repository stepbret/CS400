#ifndef POTHOLE_HPP
#define POTHOLE_HPP

#include "gameObj.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Pothole : public GameObj {
  private:
    std::string s[8];

  public:
    void draw();
    void update();
    Pothole(int y, int x);
    ~Pothole();
};
#endif
