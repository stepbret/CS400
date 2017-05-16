#include "TankLoadWindow.hpp"
#include <ncurses.h>
#include <unistd.h>

void TankLoadWindow::setupWindow() const
{
    //init_pair(1, COLOR_CYAN, COLOR_BLACK);
    //init_pair(2, COLOR_BLUE, COLOR_MAGENTA);
    //init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    wattron(win, A_BOLD);
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 3, 14, "%s", "   U   ");
    wattroff(win, COLOR_PAIR(2));
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 3, 21, "%s", "--o");
    mvwprintw(win, 4, 10, "%s", "____");
    wattroff(win, COLOR_PAIR(3)); 
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 4, 14, "%s", "       ");
    wattroff(win, COLOR_PAIR(2));
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 4, 21, "%s", "____");
    mvwprintw(win, 5, 10, "%s", "\\ O O O O O O /");
    wattroff(win, COLOR_PAIR(3)); 
    wattroff(win, A_BOLD);

    wattron(win, COLOR_PAIR(1));
    wattron(win, A_BLINK);
    mvwprintw(win, 7, ((width/2)-15), "%s", "The game is loading . . .");
    wattroff(win, COLOR_PAIR(1));
    wattroff(win, A_BLINK);
}
