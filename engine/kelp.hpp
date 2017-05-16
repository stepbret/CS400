#ifndef KELP_HPP
#define KELP_HPP

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Kelp : public background {
  private:
    std::string s[16];

  public:
    void draw();
    void update();
    bool isFull() {};
    Kelp(int y, int x);
    ~Kelp();
};
#endif
