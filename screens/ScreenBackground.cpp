#include "ScreenBackground.hpp"
#include <ncurses.h>

void ScreenBackground::setupWindow() const
{
    wattron(win, COLOR_PAIR(1));
    wbkgd(win, COLOR_PAIR(1));
    wattroff(win, COLOR_PAIR(1));
}
