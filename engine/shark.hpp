#ifndef SHARK_HPP
#define SHARK_HPP

#include "gameObj.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Shark : public GameObj {
  private:
    std::string s[3];

  public:
    void draw();
    void update();
    Shark(int y, int x);
    ~Shark();
};
#endif
