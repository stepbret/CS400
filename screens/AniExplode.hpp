#ifndef ANIEXPLODE_HPP
#define ANIEXPLODE_HPP

#include "GameWindow.hpp"

class AniExplode: public GameWindow
{
    public:
	AniExplode(int ht, int wd, int sx, int sy, int bf):GameWindow(ht, wd, sx, sy, bf){}
        virtual void setupWindow() const;
};

#endif
