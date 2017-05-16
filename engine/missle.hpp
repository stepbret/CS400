#ifndef MISSLE_HPP
#define MISSLE_HPP

#include "gameObj.hpp"

#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Missle : public GameObj {
  private:
    std::string s;

  public:
    void draw();
    void update();
    Missle(int y, int x);
    ~Missle();
};
#endif
