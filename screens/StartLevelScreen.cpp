#include "StartLevelScreen.hpp"
#include <ncurses.h>

void StartLevelScreen::setupWindow() const
{
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wattron(win, COLOR_PAIR(1));
    wattron(win, A_BOLD);
    wattron(win, A_BLINK);
    mvwprintw(win, 7, 14, "%s %d", "STARTING LEVEL ", level);
    wattroff(win, A_BLINK);
    wattroff(win, A_BOLD);
    wattroff(win, COLOR_PAIR(1));
}

void StartLevelScreen::setLevel(int lvl)
{
    level = lvl;
}

int StartLevelScreen::getLevel()
{
    return level;
}
