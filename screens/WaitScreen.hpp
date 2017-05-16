#ifndef WAITSCREEN_H
#define WAITSCREEN_H

#include "GameWindow.hpp"

class WaitScreen: public GameWindow
{
    public:
	WaitScreen(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
	virtual void setupWindow() const;
};

#endif
