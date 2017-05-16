/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 2/20/17
 ** Description: Constuctor and method definition for the 
                 building class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "background.hpp"
#include "bubbles.hpp"
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
 * Description: Builds the building
 * *******************************************************************/
Bubbles::Bubbles(int y, int x): background(4, 4, y, x) {
  s[0] = " oo ";
  s[1] = "oooo";
  s[2] = " oo ";
  s[3] = "  o ";
}  
/*********************************************************************
 *                      update()
 * Description: updates the Building windows 
 * *******************************************************************/
void Bubbles::update() {
  this->posX--;
  this->posY--;
  move_panel(pan, this->posY, this->posX);
  top_panel(pan);
  update_panels();
  doupdate();
}

bool Bubbles::isFull() {
}
/********************************************************************
 *                      draw
 * Description: Draws the building on the screen
 * ******************************************************************/
void Bubbles::draw() {
  init_pair(7, COLOR_WHITE, COLOR_BLUE);
  wattron(img, COLOR_PAIR(7));
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(7));
  update_panels();
  doupdate();
}
/*****************************************************************8
 *                          Desctructor
 * Description: Deletes the img and the panels
 * ***************************************************************/
Bubbles::~Bubbles() {
  del_panel(this->pan);
  delwin(this->img);
}
