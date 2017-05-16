#ifndef STATICSCR_H
#define STATICSCR_H

#include <ncurses.h>
#include <panel.h>
#include <vector>
#include "GameWindow.hpp"

class StaticScreen
{
protected:
    std::vector<GameWindow *> gameobjects;
    std::vector<PANEL *> screenPanels;

public:
    StaticScreen(); //default constructor
    StaticScreen(std::vector<GameWindow *> gmobj)
    {
	gameobjects = gmobj;
    }
    virtual ~StaticScreen(){}//destructor
    void setupPanels();
    virtual void setupWindow() const; //calls setupWindow() for gameobjects
					//in vector
    virtual int keyListen() const=0;
    void clearScreen();
    //getter method for gameobjects attribute
    std::vector<GameWindow *> getGameObjects();
    void setGameObjects(std::vector<GameWindow *> gmobj);
    void updatePanels();
    void deletePanels();
    void hidePanel(PANEL *pnl);
    void showPanel(PANEL *pnl);
    PANEL *getPanel(int index); 
};

#endif
