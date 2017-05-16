#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include <string>

#include "GameWindow.hpp"

class GameOverScreen: public GameWindow
{
    private:
	int dead;
	int highScore;
	int score;
	std::string highScoreList;
    public:
	GameOverScreen(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf)
	{
	    dead = 0;
	    highScore = 0;
	    score = 0;
	    highScoreList = "";
	}
	void setScore(int sc);
	void setHighScore(int hs);
	void setHighScoreList(std::string hsl);
	void setDead(int dd);
	virtual void setupWindow() const;
};

#endif
