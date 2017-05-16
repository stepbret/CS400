#include "GameOverScreen.hpp"
#include <ncurses.h>

void GameOverScreen::setupWindow() const
{
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 2, 16, "%s", "GAME OVER");
    mvwprintw(win, 11, 2, "%s", highScoreList.c_str());
    if (!dead)
    {
	mvwprintw(win, 7, 11, "%s %ld", "FINAL SCORE", score);
        if (highScore)
        {
	    wattron(win, A_BLINK);
	    mvwprintw(win, 9, 10, "%s", "THIS IS A NEW HIGH SCORE!");
	    wattroff(win, A_BLINK);
            wattroff(win, COLOR_PAIR(1));
    	}
     }
}

void GameOverScreen::setScore(int sc)
{
    score = sc;
}

void GameOverScreen::setHighScore(int hs)
{
    highScore = hs;
}

void GameOverScreen::setHighScoreList(std::string hsl)
{
    highScoreList = hsl;
}

void GameOverScreen::setDead(int dd)
{
    dead = dd;
}
