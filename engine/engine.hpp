#ifndef ENGINE_HPP
#define ENGINE_HPP


#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>
#include <vector>
#include <fstream>

#include "gameObj.hpp"
#include "background.hpp"
#include "sand.hpp"
#include "pavement.hpp"
#include "sky.hpp"
#include "player.hpp"
#include "missle.hpp"
#include "water.hpp"

class Engine {
  private:
    std::vector<background*> bg;
    std::vector<GameObj*> go;
    std::vector<Missle*> mo;
    
    int tick;
    int row;
    int col;
    bool jumping;
    int jumpDir;
    std::string levels[3];
    int nextLevel;
    bool starting;

    Sand *sand;
    Sky *sky;
    Player *po;
    Pavement *pave;
    Water *water;
    
  public:
    Engine(int row, int col);
    void setRow(int r);
    void setCol(int c);
    void addBg(background *bgPtr);
    void addGo(GameObj *goPtr);
    void addMo(Missle *m);
    void addPan(PANEL *pan);
    background* getBgPtr();
    GameObj* getGoPtr();
    void load(int level);
    bool getObs(std::ifstream &fp);
    char checkInput();
    void updateObjs(int level);
    bool detectPlayerCollisions();
    bool detectMissleCollisions();
    void updateScenery(int level);
    void getCoords(int x, int y);
    int setxCoord();
    int setyCoord();
    void run(int level);
    void endLevel(int level);
    void setScenery(int level);
    void getShoot(int shoot);
    void localcheckInput();

};
#endif
