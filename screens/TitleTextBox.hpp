#ifndef TITLETEXTBOX_H
#define TITLETEXTBOX_H

#include "GameWindow.hpp"

class TitleTextBox: public GameWindow
{
    public:
	//default Constructor
	//TitleTextBox():GameWindow(){}
	TitleTextBox(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
	virtual void setupWindow() const;
};

#endif
