#ifndef BUBBLES_HPP
#define BUBBLES_HPP

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Bubbles : public background {
  private:
    std::string s[4];

  public:
    void draw();
    void update();
    bool isFull();
    Bubbles(int y, int x);
    ~Bubbles();
};
#endif
