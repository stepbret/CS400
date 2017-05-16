/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include "whirlpool.hpp"

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
Whirlpool::Whirlpool(int y, int x): GameObj(5, 5, y, x) {
  s[0]="ooooo"; 
  s[1]="(()()";
  s[2]=" ()()";
  s[3]="  () ";
  s[4]="   v ";
  height = 0;
  
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Whirlpool::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Whirlpool::draw() {
  init_pair(17, COLOR_WHITE, COLOR_BLUE);
  wattron(img, COLOR_PAIR(17));
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(17));
  show_panel(pan);
  update_panels();
  doupdate();
}
/**********************************************************************
 *                      Destructor
 * Description: Deallocated memory associated with windows and panels
 * ********************************************************************/
Whirlpool::~Whirlpool() {
  del_panel(this->pan);
  delwin(this->img);
}
