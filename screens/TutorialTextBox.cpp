#include "TutorialTextBox.hpp"
#include <ncurses.h>

void TutorialTextBox::setupWindow() const
{
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
    wattron(win, COLOR_PAIR(1));
    wattron(win, A_BOLD);
    mvwprintw(win, 3, 16, "%s", "TUTORIAL");
    mvwprintw(win, 4, 12, "%s", "-----------------");
    wattroff(win, A_BOLD);
    mvwprintw(win, 6, 7, "%s", "PLAYER 1:");
    mvwprintw(win, 7, 10, "%s", "A . . . . . . JUMP");
    mvwprintw(win, 8, 10, "%s", "P . . . . . . SHOOT GUN");
    mvwprintw(win, 11, 7, "%s", "PLAYER 2:");
    mvwprintw(win, 12, 10, "%s", "W . . . . . . MOVE LEFT");
    mvwprintw(win, 13, 10, "%s", "L . . . . . . MOVE RIGHT");
    mvwprintw(win, 16, 7, "%s", "Press Q to return to MAIN MENU.");
    wattroff(win, COLOR_PAIR(1));
}
