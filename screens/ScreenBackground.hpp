#ifndef SCREENBACKGROUND_H
#define SCREENBACKGROUND_H

#include "GameWindow.hpp"

class ScreenBackground: public GameWindow
{
    public:
	ScreenBackground(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
	virtual void setupWindow() const;
};

#endif
