#ifndef ANIBULLET_HPP
#define ANIBULLET_HPP

#include "GameWindow.hpp"
class AniBullet: public GameWindow
{
    public:
	AniBullet(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
        virtual void setupWindow() const;
};

#endif
