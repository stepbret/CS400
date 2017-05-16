#ifndef SKY_HPP
#define SKY_HPP

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Sky : public background {
  private:
    std::vector<std::string> s;

  public:
    void draw();
    void update();
    void end();
    bool isFull();
    Sky(int r, int c, int y, int x);
    ~Sky();
};
#endif
