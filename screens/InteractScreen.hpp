#ifndef INTERACTSCR_H
#define INTERACTSCR_H

#include <ncurses.h>
#include "StaticScreen.hpp"
#include <vector>

class InteractScreen: public StaticScreen
{
    private:
	int player;
	std::vector<int> keys;
    public:
	InteractScreen(std::vector<GameWindow *> gmobj, int py, std::vector<int> ky):StaticScreen(gmobj)
	{
	    player = py;
	    keys = ky;
	}
        virtual int keyListen() const;
};

#endif
