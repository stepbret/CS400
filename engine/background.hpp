#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP


#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <panel.h>

class background {
  protected:
    int row;
    int col;
    int posY;
    int posX;
    bool start;
    WINDOW *img;
    PANEL *pan;

  public: 
    background(int r, int c, int y, int x);
    void setRows(int r);
    void setCols(int c);
    void setPosX(int x);
    void setPosY(int y);
    int getPosX();
    int getPosY();
    int getRows();
    int getCols();
    bool isStarting();
    void setStarting(bool s);
    bool checkDestroy();
    void refresh();
    PANEL* getPanel();
    virtual ~background();
    virtual void update()=0;
    virtual void draw()=0;
    virtual bool isFull()=0;

};
#endif
