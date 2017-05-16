#ifndef RLINES_HPP
#define RLINES_HPP

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class rLines : public background {
  private:
    std::string s;

  public:
    void draw();
    void update();
    bool isFull(){};
    rLines(int y, int x);
    ~rLines();
};
#endif
