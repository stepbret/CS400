/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include "cactus.hpp"

#include <ncurses.h>
#include <iostream>
#include <panel.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <cstring>

/*********************************************************************
 *                      construtor
 * Description: Adds a char array to the base class
 * *******************************************************************/
Cactus::Cactus(int y, int x): GameObj(8, 7, y, x) {
  s[0]="     _ ";
  s[1]="    / \\";
  s[2]=" _  |X|";
  s[3]="/X\\ |X|";
  s[4]="\\X\\_|X|";
  s[5]=" \\X_|X|";
  s[6]="    |X|";
  s[7]="    |X|";
  
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Cactus::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Cactus::draw() {
  init_pair(29, COLOR_GREEN, COLOR_BLACK);
  wattron(img, COLOR_PAIR(29) | A_BOLD);
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(29));
  update_panels();
  doupdate();
}
/********************************************************************
 *                      Desctructor
 * Descritpion: Destructs the objects
 * *******************************************************************/
Cactus::~Cactus() {
  del_panel(this->pan);
  delwin(this->img);
}
