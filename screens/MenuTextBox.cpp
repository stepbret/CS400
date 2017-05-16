#include "MenuTextBox.hpp"
#include <ncurses.h>

void MenuTextBox::setupWindow() const
{
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
    if (this->getBoxflag() == 1)
	box(win, 0, 0);
    //refresh();

    wattron(win, COLOR_PAIR(1));
    wattron(win, A_BOLD);

    mvwprintw(win, 5, 16, "%s", "MAIN MENU");
    mvwprintw(win, 6, 12, "%s", "-----------------");
    mvwprintw(win, 9, 12, "%s", "P . . . . . PLAY GAME");
    mvwprintw(win, 11, 12, "%s", "T . . . . . TUTORIAL");
    mvwprintw(win, 13, 12, "%s", "Q . . . . . QUIT");
    //wrefresh(win);
 
    wattroff(win, COLOR_PAIR(1));
    wattroff(win, A_BOLD);
}
