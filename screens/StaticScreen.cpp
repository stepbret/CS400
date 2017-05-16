#include "StaticScreen.hpp"
#include <vector>
#include <ncurses.h>
#include <panel.h>

void StaticScreen::setupWindow() const
{
    //call setupWindow for all GameWindow objects in vector
    for (std::vector<GameWindow *>::const_iterator it = gameobjects.begin(); it != gameobjects.end(); it++)
    {
	(*it)->setupWindow();
    }
}

void StaticScreen::clearScreen()
{
    clear();
}

//getter method for gameobjects attribute
std::vector<GameWindow *> StaticScreen::getGameObjects()
{
    return gameobjects;
}

//setter method for gameobjects attribute
void StaticScreen::setGameObjects(std::vector<GameWindow *> gmobj)
{
    gameobjects = gmobj;
}

void StaticScreen::setupPanels()
{
    for (std::vector<GameWindow *>::const_iterator it = gameobjects.begin(); it != gameobjects.end(); it++)
    {
	screenPanels.push_back(new_panel((*it)->getWin()));
    }
}

void StaticScreen::updatePanels()
{
    update_panels();	//write panels to virtual screen
    doupdate();		//show screen
}

void StaticScreen::deletePanels()
{
    for (std::vector<PANEL *>::const_iterator it = screenPanels.begin(); it != screenPanels.end(); it++)
    {
	del_panel(*it);
    }
    while (!screenPanels.empty())
    {
	screenPanels.pop_back();
    }
}

void StaticScreen::hidePanel(PANEL *pnl)
{
    if (!panel_hidden(pnl))
    {
	hide_panel(pnl);
    }
}

void StaticScreen::showPanel(PANEL *pnl)
{
    if(panel_hidden(pnl))
    {
	show_panel(pnl);
    }
}

PANEL *StaticScreen::getPanel(int index)
{
    return (screenPanels.at(index));
}
