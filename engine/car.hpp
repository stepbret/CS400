#ifndef CAR_HPP
#define CAR_HPP

#include "gameObj.hpp"
#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Car : public GameObj {
  private:
    std::string s[3];

  public:
    void draw();
    void update();
    Car(int y, int x);
    ~Car();

};
#endif
