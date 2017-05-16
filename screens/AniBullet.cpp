#include "AniBullet.hpp"
#include <ncurses.h>

void AniBullet::setupWindow() const
{
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, 0, 0, "%s", "*");
    wattroff(win, COLOR_PAIR(4));
}
