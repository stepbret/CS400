#include "EndLevelScreen.hpp"
#include <ncurses.h>
#include <string>

void EndLevelScreen::setupWindow() const
{
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wattron(win, COLOR_PAIR(1));
    wattron(win, A_BOLD);
    mvwprintw(win, 7, 14, "%s %d", "END OF LEVEL ", level);
    wattroff(win, A_BOLD);
    if (levelseconds < 10)
    {
        mvwprintw(win, 11, 12, "LEVEL TIME: %d:0%d", levelminutes, levelseconds);
    }
    else
        mvwprintw(win, 11, 12, "LEVEL TIME: %d:%d", levelminutes, levelseconds);
    mvwprintw(win, 13, 12, "LEVEL SCORE: %d", score);
    wattroff(win, A_BOLD);
    wattroff(win, COLOR_PAIR(1));
}

void EndLevelScreen::setLevel(int lvl)
{
    level = lvl;
}

int EndLevelScreen::getLevel()
{
    return level;
}

void EndLevelScreen::setScore(int gmscore)
{
    score = gmscore;
}

int EndLevelScreen::getScore()
{
    return score;
}

void EndLevelScreen::setLevelMinutes(int min)
{
    levelminutes = min;
}

void EndLevelScreen::setLevelSeconds(int sec)
{
    levelseconds = sec;
}
