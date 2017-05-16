#include "screens.hpp"
#include <ncurses.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <sstream>

//method to convert int to string in C++98
/*from: http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c*/
std::string intToString(int i)
{
    std::ostringstream temp;
    temp<<i;
    return temp.str();
}

int main()
{
    int keypress, keypress2, keypress3;
    
    initscr();		//start ncurses mode
    curs_set(0); 	//make cursor invisible
    start_color();	//turn on ncurses color mode
    noecho();		//don't write keyboard input to screen

    /******DEFINE COLOR PAIRS******/
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_MAGENTA);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
/****************************************************************************
 * code for setting up status window that will display connection status
 *in non-game mode and game score/time in game-play mode
****************************************************************************/
//    TextScreen statusBar(5, COLS-6, 3, 3, 0, "Behold, the game statusbar!", 1, 1); //textscreen with no
							//text or border
    
/*****************************************************************************
 * code for setting up and displaying load screen			
 * **************************************************************************/
    //set up for load screen
    //set up vector containing titlebox, tankwindow
    Screens *displayScr;
    displayScr = new Screens();

    displayScr->displayScreen(displayScr->getScreen(0));
    displayScr->animateBullet();
    displayScr->teardownScreen(displayScr->getScreen(0));

/****************************************************************************
 * strings that contain end level information				    *
 ***************************************************************************/
    long endscores[] = {2000, 3500, 5000};
    std::string endtime[] = {"01:50", "02:05", "02:31"};

    while(1)
    {
    	displayScr->displayScreen(displayScr->getScreen(1));
    	do
    	{ 
            //return value from keypress (wait for input)
            keypress = (displayScr->getScreen(1))->keyListen();
    	}while(keypress < 0);    

    	displayScr->teardownScreen(displayScr->getScreen(1));

    	switch(keypress)
    	{
	    case 'q':
	    case 'Q':
	    	endwin();
	    	exit(0);	//quit game
	    case 't': 
	    case 'T':
	    	displayScr->displayScreen(displayScr->getScreen(2));
	    	do
	    	{
		    keypress2 = (displayScr->getScreen(2))->keyListen();
	    	}while(keypress2 < 0);
	        displayScr->teardownScreen(displayScr->getScreen(2));
	        break;
	    case 'p':
	    case 'P':
		//connect to server here
		//show waitscreen for now
		displayScr->displayScreen(displayScr->getScreen(3));
		/*do
		{
		    keypress3 = waitscr.keyListen();
		}while(keypress3 < 0);*/
		usleep(2000000);
		displayScr->teardownScreen(displayScr->getScreen(3));

		for (int i = 0; i < 3; i++)
		{
		    //set up start level screen
		    (displayScr->getStartScreen())->setLevel(i+1);
		    displayScr->displayScreen(displayScr->getScreen(4));
		    usleep(2000000);
		    displayScr->teardownScreen(displayScr->getScreen(4));

		    //set up end level screen
		    (displayScr->getEndLevelScreen())->setLevel(i+1);
		    (displayScr->getEndLevelScreen())->setScore(endscores[i]);
		    (displayScr->getEndLevelScreen())->setTime(endtime[i]);
		    displayScr->displayScreen(displayScr->getScreen(5));
		    usleep(2000000);
		    displayScr->teardownScreen(displayScr->getScreen(5));
		}
		//set up game over screen(dead)
		(displayScr->getGameOver())->setDead(1);
		(displayScr->getGameOver())->setHighScore(0);
		displayScr->displayScreen(displayScr->getScreen(6));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(2));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(3));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(4));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(5));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(6));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(7));
    		(displayScr->getScreen(6))->updatePanels(); 
		usleep(2000000);
		displayScr->teardownScreen(displayScr->getScreen(6));

		//set up game over screen(end game)
		(displayScr->getGameOver())->setDead(0);
		(displayScr->getGameOver())->setScore(3000);
		(displayScr->getGameOver())->setHighScore(0);
		displayScr->displayScreen(displayScr->getScreen(6));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(2));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(3));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(4));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(5));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(6));
		(displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(7));
    		(displayScr->getScreen(6))->updatePanels(); 
		usleep(2000000);
		displayScr->teardownScreen(displayScr->getScreen(6));
		
		//set up game over screen (high score)
		(displayScr->getGameOver())->setScore(3000);
		(displayScr->getGameOver())->setHighScore(1);
		displayScr->displayScreen(displayScr->getScreen(6));
		displayScr->animateFireworks();
		displayScr->teardownScreen(displayScr->getScreen(6));

		break;
        }
    }
    endwin();
    delete displayScr;
    //std::cout << "keypress value: " << keypress << std::endl;
    return 0;
}
