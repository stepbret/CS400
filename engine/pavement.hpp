#ifndef PAVEMENT_HPP
#define PAVEMENT_HPP

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Pavement : public background {
  private:
    std::vector<std::string> s;

  public:
    void draw();
    void update();
    void start();
    void end();
    bool isFull();
    Pavement(int r, int c, int y, int x);
    ~Pavement();
};
#endif
