/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include "shark.hpp"

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
Shark::Shark(int y, int x): GameObj(3, 9, y, x) {
  s[0]="__/(____/";
  s[1]=">`))__v-\\";
  s[2]="   \\(    ";
  
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Shark::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Shark::draw() {
  init_pair(18, COLOR_BLUE, COLOR_BLACK);
  wattron(img, COLOR_PAIR(18) | A_STANDOUT);
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(18));
  show_panel(pan);
  update_panels();
  doupdate();
}
/*********************************************************************
 *                      Desctructor
 * Description: Destroys the object
 * *******************************************************************/
Shark::~Shark() {
  del_panel(this->pan);
  delwin(this->img);
}


