#ifndef QUICKSAND_HPP
#define QUICKSAND_HPP

#include "gameObj.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class QuickSand : public GameObj {
  private:
    std::string s[8];

  public:
    void draw();
    void update();
    QuickSand(int y, int x);
    ~QuickSand();
};
#endif
