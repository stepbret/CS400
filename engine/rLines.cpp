/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 2/20/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "background.hpp"
#include "rLines.hpp"
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
rLines::rLines(int y, int x): background(1, 7, y, x) {
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void rLines::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void rLines::draw() {
  init_pair(10, COLOR_WHITE, COLOR_YELLOW);
  wbkgd(img, COLOR_PAIR(10));
  update_panels();
  doupdate();
}
/******************************************************************
 *                      Desctructor
 * Description: Destroys the panels and the associated img
 * ****************************************************************/
rLines::~rLines() {
  del_panel(this->pan);
  delwin(this->img);
}
