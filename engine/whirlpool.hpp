#ifndef WHIRLPOOL_HPP
#define WHIRLPOOL_HPP

#include "gameObj.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Whirlpool : public GameObj {
  private:
    std::string s[8];

  public:
    void draw();
    void update();
    int height;
    Whirlpool(int y, int x);
    ~Whirlpool();
};
#endif
