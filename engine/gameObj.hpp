#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP


#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>

class GameObj {
  protected:
    int row;
    int col;
    int posY;
    int posX;
    WINDOW *img;
    PANEL *pan;

  public: 
    GameObj(int r, int c, int y, int x);
    void setRows(int r);
    void setCols(int c);
    void setPosX(int x);
    void setPosY(int y);
    int getPosX();
    int getPosY();
    int getRows();
    int getCols();
    bool checkDestroy();
    WINDOW* getWin();
    PANEL* getPanel();
    void hide();
    virtual void update()=0;
    virtual void draw()=0;
    virtual ~GameObj();

};
#endif
