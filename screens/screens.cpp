#include "screens.hpp"
#include <ncurses.h>
#include <unistd.h>

Screens::Screens()
{
    //set up objects for loading screen
    titleBox = new TitleTextBox(15, 40, ((COLS - 40)/2), (((LINES )/2) - 10), 1);
    tankLoadWin = new TankLoadWindow(10, 40, ((COLS - 40)/2), (((LINES)/2) + 5), 0);
    anibullet = new AniBullet(1, 1, ((COLS/2)+4), ((LINES/2)+8), 0);
    aniexplode = new AniExplode(2, 7, ((COLS/2)+10), ((LINES/2)+8), 0); 
    loadobj.push_back(titleBox);
    loadobj.push_back(tankLoadWin);
    loadobj.push_back(anibullet);
    loadobj.push_back(aniexplode);
    loadScreen = new InteractScreen(loadobj, 0, std::vector<int>());
    screens.push_back(loadScreen);
 
    //set up objects for menu screen
    menubox = new MenuTextBox(20, 40, ((COLS/2)-20), ((LINES/2)-10), 1);
    menukeys.push_back('p');
    menukeys.push_back('P');
    menukeys.push_back('q');
    menukeys.push_back('Q');
    menukeys.push_back('t');
    menukeys.push_back('T');
    gameobj.push_back(menubox);
    menuScreen = new InteractScreen(gameobj, 0, menukeys);
    screens.push_back(menuScreen);

    //set up object for tutorial screen
    tutorialBox = new TutorialTextBox(20, 40, ((COLS - 40)/2), ((LINES - 20)/2), 1);
    tutorkeys.push_back('q');
    tutorkeys.push_back('Q');
    tutorobj.push_back(tutorialBox);
    tutorScreen = new InteractScreen(tutorobj, 0, tutorkeys);
    screens.push_back(tutorScreen);

    //set up object for wait screen
    waitscrobj = new WaitScreen(20, 40, ((COLS - 40)/2), ((LINES - 20)/2), 1);
    waitkeys.push_back('q');
    waitkeys.push_back('Q');
    waitobj.push_back(waitscrobj);
    waitscr = new InteractScreen(waitobj, 1, waitkeys);
    screens.push_back(waitscr);

    //set up object for start level screen
    startlvl = new StartLevelScreen(20, 40, ((COLS - 40)/2), ((LINES - 20)/2), 1);
    screenbkgd = new ScreenBackground(LINES, COLS,0, 0, 0);
    startobj.push_back(screenbkgd);
    startobj.push_back(startlvl);
    startlvlScreen = new InteractScreen(startobj, 0, std::vector<int>());
    screens.push_back(startlvlScreen);

    //set up object for end level screen
    endlvl = new EndLevelScreen(20, 40, ((COLS - 40)/2), ((LINES - 20)/2), 1);
    endobj.push_back(screenbkgd);
    endobj.push_back(endlvl);
    endlvlScreen = new InteractScreen(endobj, 0, std::vector<int>());
    screens.push_back(endlvlScreen);

    //set up object for gameover screen (high score)
    gameover = new GameOverScreen(20, 40, ((COLS - 40)/2), (((LINES - 15)/2)), 1);
    fireworks1 = new Fireworks(1, 1, (((COLS)/2)-1), (((LINES - 18)/2)), 0);
    fireworks2 = new Fireworks(1, 1, ((COLS)/2), (((LINES - 18)/2)), 0);
    fireworks3 = new Fireworks(1, 1, (((COLS)/2)+1), (((LINES - 18)/2)), 0);
    aniexplode1 = new AniExplode(2, 7, ((COLS/2)-6), (((LINES-18)/2)-3), 0); 
    aniexplode2 = new AniExplode(2, 7, ((COLS/2)-1), (((LINES-18)/2)-5), 0); 
    aniexplode3 = new AniExplode(2, 7, ((COLS/2)+4), (((LINES-18)/2)-3), 0); 
    gameoverobj.push_back(screenbkgd);
    gameoverobj.push_back(gameover);
    gameoverobj.push_back(fireworks1);
    gameoverobj.push_back(fireworks2);
    gameoverobj.push_back(fireworks3);
    gameoverobj.push_back(aniexplode1);
    gameoverobj.push_back(aniexplode2);
    gameoverobj.push_back(aniexplode3);
    gameoverScr = new InteractScreen(gameoverobj, 0, std::vector<int>());
    screens.push_back(gameoverScr);

    //set up object for status bar screen
    statusbar = new StatusWindow(3, 30, (((COLS-30)/2)), 2, 1);
    statuswinobj.push_back(statusbar);
    statusBarScr = new InteractScreen(statuswinobj, 0, std::vector<int>());
    screens.push_back(statusBarScr);
}

Screens::~Screens()
{
    delete titleBox;
    delete tankLoadWin;
    delete loadScreen;
    delete anibullet;
    delete aniexplode;
    delete menubox;
    delete menuScreen;
    delete tutorialBox;
    delete tutorScreen;
    delete waitscrobj;
    delete waitscr;
    delete screenbkgd;
    delete startlvl;
    delete startlvlScreen;
    delete endlvl;
    delete endlvlScreen;
    delete gameover;
    delete gameoverScr;
    delete fireworks1;
    delete fireworks2;
    delete fireworks3;
    delete aniexplode1;
    delete aniexplode2;
    delete aniexplode3;
    delete statusbar;
    delete statusBarScr;
}

void Screens::setScreen(StaticScreen *newscr)
{
    screens.push_back(newscr);
}
    
StaticScreen *Screens::getScreen(int index)
{
    if (index < screens.size())
    {
        return screens.at(index);
    }
}

StartLevelScreen *Screens::getStartScreen()
{
    return startlvl;
}

EndLevelScreen *Screens::getEndLevelScreen()
{
    return endlvl;
}

AniBullet *Screens::getAniBullet()
{
    return anibullet;
}

AniExplode *Screens::getAniExplode()
{
    return aniexplode;
}

GameOverScreen *Screens::getGameOverWin()
{
    return gameover;
}

Fireworks *Screens::getFireworks1()
{
    return fireworks1;
}

Fireworks *Screens::getFireworks2()
{
    return fireworks2;
}

Fireworks *Screens::getFireworks3()
{
    return fireworks3;
}

StatusWindow *Screens::getStatusBar()
{
    return statusbar;
}

void Screens::displayScreen(StaticScreen *screen)
{
    screen->setupWindow();
    screen->setupPanels();
    screen->updatePanels();
}

void Screens::teardownScreen(StaticScreen *screen)
{
    screen->deletePanels();
    screen->clearScreen();
}

void Screens::animateBullet()
{
    for (int i = 0; i < 3; i++)
    {
        //hide explosion panel
        (this->getScreen(0))->hidePanel((this->getScreen(0))->getPanel(3));
        //move bullet object
        (this->getAniBullet())->setStartX((COLS/2)+4);
        move_panel(((this->getScreen(0))->getPanel(2)),((this->getAniBullet())->getStartY()), ((COLS/2)+4));
        (this->getScreen(0))->updatePanels();
        usleep(500000);
        (this->getAniBullet())->setStartX((COLS/2)+6);
        move_panel(((this->getScreen(0))->getPanel(2)),((this->getAniBullet())->getStartY()), ((COLS/2)+6));
        (this->getScreen(0))->updatePanels();
        usleep(500000);
        (this->getAniBullet())->setStartX((COLS/2)+8);
        move_panel(((this->getScreen(0))->getPanel(2)),((this->getAniBullet())->getStartY()), ((COLS/2)+8));
        (this->getScreen(0))->updatePanels();
        usleep(500000);
        (this->getAniBullet())->setStartX((COLS/2)+10);
        move_panel(((this->getScreen(0))->getPanel(2)),((this->getAniBullet())->getStartY()), ((COLS/2)+10));
        (this->getScreen(0))->updatePanels();
        usleep(500000);
        //show explosion panel
        (this->getScreen(0))->showPanel((this->getScreen(0))->getPanel(3));
        (this->getScreen(0))->updatePanels();
        usleep(500000);
    }
}

void Screens::animateFireworks()
{
    for (int i =0; i < 5; i++)
    {
        //hide explosion panels
        (this->getScreen(6))->hidePanel((this->getScreen(6))->getPanel(5));
        (this->getScreen(6))->hidePanel((this->getScreen(6))->getPanel(6));
        (this->getScreen(6))->hidePanel((this->getScreen(6))->getPanel(7));
        //move fireworks
        //for first firework:
        (this->getFireworks1())->setStartX((COLS/2)-1);
        (this->getFireworks1())->setStartY(((LINES-18)/2));
        move_panel(((this->getScreen(6))->getPanel(2)),((this->getFireworks1())->getStartY()), ((this->getFireworks1()->getStartX())));
        //for second firework
        (this->getFireworks2())->setStartY(((LINES-18)/2));
        move_panel(((this->getScreen(6))->getPanel(3)),((this->getFireworks2())->getStartY()), ((this->getFireworks2()->getStartX())));
        //for third firework
        (this->getFireworks3())->setStartX((COLS/2)+1);
        (this->getFireworks3())->setStartY(((LINES-18)/2));
        move_panel(((this->getScreen(6))->getPanel(4)),((this->getFireworks3())->getStartY()), ((this->getFireworks3()->getStartX())));
        (this->getScreen(6))->updatePanels();
        usleep(500000);
        //move fireworks
        //for first firework:
        (this->getFireworks1())->setStartX((COLS/2)-3);
        (this->getFireworks1())->setStartY(((LINES-18)/2)-1);
        move_panel(((this->getScreen(6))->getPanel(2)),((this->getFireworks1())->getStartY()), ((this->getFireworks1()->getStartX())));
        //for second firework
        (this->getFireworks2())->setStartY(((LINES-18)/2)-2);
        move_panel(((this->getScreen(6))->getPanel(3)),((this->getFireworks2())->getStartY()), ((this->getFireworks2()->getStartX())));
        //for third firework
        (this->getFireworks3())->setStartX((COLS/2)+3);
        (this->getFireworks3())->setStartY(((LINES-18)/2)-1);
        move_panel(((this->getScreen(6))->getPanel(4)),((this->getFireworks3())->getStartY()), ((this->getFireworks3()->getStartX())));
        (this->getScreen(6))->updatePanels();
        usleep(500000);

        //move fireworks
        //for first firework:
        (this->getFireworks1())->setStartX((COLS/2)-5);
        (this->getFireworks1())->setStartY(((LINES-18)/2)-2);
        move_panel(((this->getScreen(6))->getPanel(2)),((this->getFireworks1())->getStartY()), ((this->getFireworks1()->getStartX())));
        //for second firework
        (this->getFireworks2())->setStartY(((LINES-18)/2)-4);
        move_panel(((this->getScreen(6))->getPanel(3)),((this->getFireworks2())->getStartY()), ((this->getFireworks2()->getStartX())));
        //for third firework
        (this->getFireworks3())->setStartX((COLS/2)+5);
        (this->getFireworks3())->setStartY(((LINES-18)/2)-2);
        move_panel(((this->getScreen(6))->getPanel(4)),((this->getFireworks3())->getStartY()), ((this->getFireworks3()->getStartX())));
        (this->getScreen(6))->updatePanels();
        usleep(500000);

        (this->getScreen(6))->showPanel((this->getScreen(6))->getPanel(5));
        (this->getScreen(6))->showPanel((this->getScreen(6))->getPanel(6));
        (this->getScreen(6))->showPanel((this->getScreen(6))->getPanel(7));
        (this->getScreen(6))->updatePanels();
        usleep(500000);
    }
}
