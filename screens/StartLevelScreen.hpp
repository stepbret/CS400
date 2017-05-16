#ifndef STARTLEVELSCREEN_H
#define STARTLEVELSCREEN_H

#include "GameWindow.hpp"

class StartLevelScreen: public GameWindow
{
    protected:
	int level;

    public:
	StartLevelScreen(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
    	virtual void setupWindow() const;
	void setLevel(int lvl);
	int getLevel();
};

#endif
