#include "StatusWindow.hpp"
#include <string>
#include <ncurses.h>

void StatusWindow::setupWindow() const
{
    if (this->getBoxflag() == 1)
	box(win, 0, 0);
    wattron(win, COLOR_PAIR(1));
    wbkgd(win, COLOR_PAIR(1));
    if (levelseconds < 10)
    {
        mvwprintw(win, 1, 1, "SCORE: %d\tTIME: %d:0%d", score, levelminutes, levelseconds);
    }
    else
    {
        mvwprintw(win, 1, 1, "SCORE: %d\tTIME: %d:%d", score, levelminutes, levelseconds);
    }
    wattroff(win, COLOR_PAIR(1));
}

void StatusWindow::setScore(int gmscore)
{
    score = gmscore;
}

int StatusWindow::getScore()
{
    return score;
}

void StatusWindow::setLevelSeconds(int sec)
{
    levelseconds = sec;
}

void StatusWindow::setLevelMinutes(int min)
{
    levelminutes = min;
}

int StatusWindow::getLevelSeconds()
{
    return levelseconds;
}

int StatusWindow::getLevelMinutes()
{
    return levelminutes;
}
