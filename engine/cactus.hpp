#ifndef CACTUS_HPP
#define CACTUS_HPP

#include "gameObj.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Cactus : public GameObj {
  private:
    std::string s[8];

  public:
    void draw();
    void update();
    Cactus(int y, int x);
    ~Cactus();

};
#endif
