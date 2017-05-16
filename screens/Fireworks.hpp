#ifndef FIREWORKS_HPP
#define FIREWORKS_HPP

#include "GameWindow.hpp"

class Fireworks: public GameWindow
{
    private:
	int color;

    public:
	Fireworks(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){color=1;}
	void setColor(int cl);
	void setupWindow() const;
};

#endif
