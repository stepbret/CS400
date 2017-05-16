#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "gameObj.hpp"
#include "../netcode/clientpacket.h"

#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <string>
#include <vector>

class Player : public GameObj {
  private:
    std::string s[3];
    int level;

  public:
    void draw();
    void forward();
    void backward();
    void jumpUp();
    void jumpDown();
    void shoot();
    void checkInput();
    void update();
    void setLevel(int);
    Player(int y, int x);
    ~Player();
};
#endif
