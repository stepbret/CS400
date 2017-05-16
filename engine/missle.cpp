/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include "missle.hpp"

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
Missle::Missle(int y, int x): GameObj(1, 4, y, x) {
  s = "~X=>";
}  
/*********************************************************************
 *                      update()
 * Description: Moves the missle forward it moves faster than the game 
 * *******************************************************************/
void Missle::update() {
  this->posX++;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}
/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Missle::draw() {
  init_pair(14, COLOR_RED, COLOR_BLACK);
  wattron(img, COLOR_PAIR(14));
  wprintw(img,"%s", s.c_str());
  wattroff(img, COLOR_PAIR(14));
  show_panel(pan);
  update_panels();
  doupdate();
}

/******************************************************************
 *                      Destructor
 * ***************************************************************/
Missle::~Missle() {
  del_panel(this->pan);
  delwin(this->img);
}
