#include "TitleTextBox.hpp"
#include <ncurses.h>

void TitleTextBox::setupWindow() const
{
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wattron(win, COLOR_PAIR(1));
    wattron(win, A_BOLD);
    wbkgd(stdscr, COLOR_PAIR(1));  	//set screen bkgrd color
					//to be black 
    mvwprintw(win, 2, 16, "%s", "TANK RUN");
    wattroff(win, A_BOLD);
    mvwprintw(win, 7, 13, "%s", "Jason McAnally");
    mvwprintw(win, 8, 12, "%s", "Brittney McInnis");
    mvwprintw(win, 9, 12, "%s", "Brett Stephenson");
    //wrefresh(win);
    wattroff(win, COLOR_PAIR(1));
}
