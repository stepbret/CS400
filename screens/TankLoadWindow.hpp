#ifndef TANKLOADWINDOW_H
#define TANKLOADWINDOW_H

#include "GameWindow.hpp"

class TankLoadWindow: public GameWindow
{
    public:
	//default Constructor
	//TankLoadWindow():GameWindow(){}
	TankLoadWindow(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
	virtual void setupWindow() const;
};

#endif
