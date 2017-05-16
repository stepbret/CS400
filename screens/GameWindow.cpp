#include "GameWindow.hpp"
#include <ncurses.h>

//constructor
GameWindow::GameWindow(int ht, int wd, int sx, int sy, int bf)
{
    setHeight(ht);
    setWidth(wd);
    setStartY(sy);
    setStartX(sx);
    setBoxFlag(bf);
    createWindow(); 
}

void GameWindow::setHeight(int ht)
{
    height = ht;
}

void GameWindow::setWidth(int wd)
{
    width = wd;
}

void GameWindow::setStartY(int sy)
{
    starty = sy;
}

void GameWindow::setStartX(int sx)
{
    startx = sx;
}

void GameWindow::setBoxFlag(int bf)
{
    boxflag = bf;
}

int GameWindow::getHeight()
{
    return height;
}

int GameWindow::getWidth()
{
    return width;
}

int GameWindow::getStartY()
{
    return starty;
}

int GameWindow::getStartX() 
{
    return startx;
}

int GameWindow::getBoxflag() const
{
    return boxflag;
}

WINDOW *GameWindow::getWin()
{
    return win;
}
