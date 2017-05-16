#ifndef SCREENS_H
#define SCREENS_H

#include "GameWindow.hpp"
#include "InteractScreen.hpp"
#include "MenuTextBox.hpp"
#include "StaticScreen.hpp"
#include "TankLoadWindow.hpp"
#include "TitleTextBox.hpp"
#include "TutorialTextBox.hpp"
#include "WaitScreen.hpp"
#include "StartLevelScreen.hpp"
#include "EndLevelScreen.hpp"
#include "TextScreen.hpp"
#include "AniBullet.hpp"
#include "AniExplode.hpp"
#include "Fireworks.hpp"
#include "GameOverScreen.hpp"
#include "ScreenBackground.hpp"
#include "StatusWindow.hpp"
#include <vector>

class Screens
{
    private:
	std::vector<StaticScreen *> screens; //for screens
	std::vector<StaticScreen *> gameoverScreens;//for game over screens
	std::vector<int> menukeys;//for menu screen keys 
	std::vector<int> tutorkeys;//for tutorial screen keys
	std::vector<int> waitkeys;//for wait screen keys

	std::vector<GameWindow *> loadobj;//to hold load screen objects
	std::vector<GameWindow *> gameobj;//to hold menu screen objects
	std::vector<GameWindow *> tutorobj;//to hold tutorial screen objects
	std::vector<GameWindow *> waitobj;//to hold wait screen objects
	std::vector<GameWindow *> startobj;//to hold start lvl objects
	std::vector<GameWindow *> endobj;//to hold end lvl objects
	std::vector<GameWindow *> gameoverobj;//to hold game over objects
	std::vector<GameWindow *> statuswinobj; //to hold status bar objects

	GameWindow *titleBox;
	GameWindow *tankLoadWin;
	AniBullet *anibullet;
	AniExplode *aniexplode;
	AniExplode *aniexplode1;
	AniExplode *aniexplode2;
	AniExplode *aniexplode3;
	GameWindow *menubox;
	GameWindow *tutorialBox;
	GameWindow *waitscrobj;
	StartLevelScreen *startlvl;
	EndLevelScreen *endlvl;
	GameOverScreen *gameover;
	Fireworks *fireworks1;
	Fireworks *fireworks2;
	Fireworks *fireworks3;
	GameWindow *screenbkgd;
	StatusWindow *statusbar;
	
	InteractScreen *loadScreen;
	InteractScreen *menuScreen;
	InteractScreen *tutorScreen;
	InteractScreen *waitscr;
	InteractScreen *startlvlScreen;
	InteractScreen *endlvlScreen;
	InteractScreen *gameoverScr;	
	InteractScreen *statusBarScr;

    public:
	Screens(); //default constructor
	~Screens(); //destructor
	void setScreen(StaticScreen *newscr);
	StaticScreen *getScreen(int index);
	StartLevelScreen *getStartScreen();
	EndLevelScreen *getEndLevelScreen();
	AniBullet *getAniBullet();
	AniExplode *getAniExplode();
	GameOverScreen *getGameOverWin();
	Fireworks *getFireworks1();
	Fireworks *getFireworks2();
	Fireworks *getFireworks3();
	StatusWindow * getStatusBar();
	void displayScreen(StaticScreen *screen);
	void teardownScreen(StaticScreen *screen);
	void animateBullet();
	void animateFireworks();
};

#endif
