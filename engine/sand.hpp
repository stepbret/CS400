#ifndef SAND_HPP
#define SAND_HPP

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Sand : public background {
  private:
    std::vector<std::string> s;

  public:
    void draw();
    void update();
    void start();
    void end();
    void hide();
    bool isFull();
    Sand(int r, int c, int y, int x);
    virtual ~Sand();
};
#endif
