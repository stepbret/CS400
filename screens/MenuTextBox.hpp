#ifndef MENUTEXTBOX_H
#define MENUTEXTBOX_H

#include "GameWindow.hpp"

class MenuTextBox: public GameWindow
{
    public:
	MenuTextBox(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
	virtual void setupWindow() const;
};

#endif
