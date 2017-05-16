#include <ncurses.h>
#include "InteractScreen.hpp"
#include <vector>
#include <algorithm> //for std::find

/*Note: initscr() must be called before this function*/
int InteractScreen::keyListen() const{
    int ch;
    raw(); 	//key press immediately read and processed
    noecho();   //key press will not be echoed to screen 
    //keypad(win, TRUE);	//enables reading arrow keys, etc.
    if (player > 0)
	halfdelay(5); 	//waits for input for 0.5 seconds
    ch = getch();
    if (ch >= 0){
	if (std::find(keys.begin(), keys.end(), ch) != keys.end())
	    return ch;
    }
    return -1;
}
