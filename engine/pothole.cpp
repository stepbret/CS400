/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include "pothole.hpp"

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
Pothole::Pothole(int y, int x): GameObj(6, 8, y, x) {
  s[0]="        "; 
  s[1]="\\\\___//";
  s[2]="\\\\php//";
  s[3]="\\phphp//";
  s[4]="\\phph//";
  s[5]="\\phph//";
  
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Pothole::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Pothole::draw() {
  init_pair(9, COLOR_RED, COLOR_BLACK);
  wattron(img, COLOR_PAIR(9) | A_BOLD);
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(9));
  show_panel(pan);
  update_panels();
  doupdate();
}
/***********************************************************************
 *                       desctructor
 * Description: Destroys the panels and img
 * *********************************************************************/
Pothole::~Pothole() {
  del_panel(this->pan);
  delwin(this->img);
}
