#include "Fireworks.hpp"
#include <ncurses.h>

void Fireworks::setupWindow() const
{
    wattron(win, COLOR_PAIR(color));
    mvwprintw(win, 0, 0, "%s", ".");
    wattroff(win, COLOR_PAIR(color));
}

void Fireworks::setColor(int cl)
{
    color = cl;
}
