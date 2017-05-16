#include "AniExplode.hpp"
#include <ncurses.h>

void AniExplode::setupWindow() const
{
    wattron(win, COLOR_PAIR(5));
    mvwprintw(win, 0, 0, "%s", "_\\/_");	
    mvwprintw(win, 1, 0, "%s", " /\\ ");
    wattroff(win, COLOR_PAIR(5));
}
