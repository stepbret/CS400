#include "screens.hpp"
#include "Tank.hpp"
#include "Cloud.hpp"
#include "Background.hpp"
#include "Sand.hpp"
#include <ncurses.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>

/*from: http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c*/
std::string intToString(int i)
{
    std::ostringstream temp;
    temp<<i;
    return temp.str();
}

void displayScreen(StaticScreen *screen)
{
    screen->setupWindow();
    screen->setupPanels();
    screen->updatePanels();
}

void teardownScreen(StaticScreen *screen)
{
    screen->deletePanels();
    screen->clearScreen();
}

int main()
{
    initscr();		//start ncurses mode
    curs_set(0); 	//make cursor invisible
    start_color();	//turn on ncurses color mode
    noecho();		//don't write keyboard input to screen

    std::vector<GameWindow *> screenObj;

    Background bkgrd(LINES, COLS, 0, 0, 0);
    Sand sand(17, COLS, 0, 28, 0);
    Tank tank(3, 15, 20, 25, 0);
    Cloud cloud1(3, 4, 40, 15, 0);
    Cloud cloud2(3, 4, 20, 20, 0);
    Cloud cloud3(3, 4, 35, 23, 0);
    TextScreen statusBar(5, COLS-6, 3, 3, 1, "Score: 1000\tTime: 01:10", 1, 1);

    screenObj.push_back(&bkgrd);
    screenObj.push_back(&sand);
    screenObj.push_back(&cloud1);
    screenObj.push_back(&cloud2);
    screenObj.push_back(&cloud3);
    screenObj.push_back(&tank);
    screenObj.push_back(&statusBar);

    StaticScreen screen(screenObj);
    displayScreen(&screen);

    int newy1, newx1, newy2, newx2, newy3, newx3, tanky, tankx, score=1000, gmtime=10, life=10;
    for (int i = 0; i < 10; i++)
    {
	std::string str = "Score: ";
	newy1 = cloud1.getStartY();
	newx1 = cloud1.getStartX();
	newx1--;
	cloud1.setStartX(newx1);
	newy2 = cloud2.getStartY();
	newx2 = cloud2.getStartX();
	newx2--;
	cloud2.setStartX(newx2);
	newy3 = cloud3.getStartY();
	newx3 = cloud3.getStartX();
	newx3--;
	cloud3.setStartX(newx3);
	tanky = tank.getStartY();
	tankx = tank.getStartX();
	tankx++;
	tank.setStartX(tankx);
	life--;
	score += 20;
        gmtime += 1;
	str.append(intToString(score));
	str.append("\tTime: 01:");
	str.append(intToString(gmtime));
	str.append("\tLife: ");
	str.append(intToString(life));
	statusBar.setString(str);
	statusBar.clearWindow();
	statusBar.setupWindow();
	move_panel(screen.getPanel(2), newy1, newx1);
	move_panel(screen.getPanel(3), newy2, newx2);
	move_panel(screen.getPanel(4), newy3, newx3);
	move_panel(screen.getPanel(5), tanky, tankx);
	refresh();
	screen.updatePanels();
	usleep(1000000);
    }
    teardownScreen(&screen);
    endwin();
    return 0;
}
