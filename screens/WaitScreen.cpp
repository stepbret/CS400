#include "WaitScreen.hpp"
#include <ncurses.h>

void WaitScreen::setupWindow() const
{
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wattron(win, COLOR_PAIR(1));
    wattron(win, A_BOLD);
    wattron(win, A_BLINK);
    mvwprintw(win, 7, 12, "%s", "WAITING FOR PLAYER 2");
    wattroff(win, COLOR_PAIR(1));
    wattroff(win, A_BOLD);
    wattroff(win, A_BLINK);
}
