#ifndef STATUSWINDOW_HPP
#define STATUSWINDOW_HPP

#include "GameWindow.hpp"
#include <string>

class StatusWindow: public GameWindow
{
    private:
	int score;
	int levelseconds;
	int levelminutes;

    public:
	StatusWindow(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf)
	{
	    score = 0;
	    levelseconds = 0;
	    levelminutes = 0;
	}
	virtual void setupWindow() const;
	void setScore(int gmscore);
	int getScore();
	void setLevelSeconds(int sec);
	void setLevelMinutes(int min);
	int getLevelSeconds();
	int getLevelMinutes();
};

#endif
