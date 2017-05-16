#ifndef ENDLEVELSCREEN_H
#define ENDLEVELSCREEN_H

#include "GameWindow.hpp"
#include <string>

class EndLevelScreen: public GameWindow
{
    protected:
	int level;
	int score;
	int levelminutes;
	int levelseconds;   
 
    public:
	EndLevelScreen(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
	virtual void setupWindow() const;
	void setLevel(int lvl);
	int getLevel();
	void setScore(int gmscore);
	int getScore();
	void setLevelMinutes(int min);
	void setLevelSeconds(int sec);
};

#endif
