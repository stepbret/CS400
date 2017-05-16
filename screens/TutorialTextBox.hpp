#ifndef TUTORIALTEXTBOX_H
#define TUTORIALTEXTBOX_H

#include "GameWindow.hpp"

class TutorialTextBox: public GameWindow
{
    public:
	TutorialTextBox(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
	virtual void setupWindow() const;
};

#endif
