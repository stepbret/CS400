/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 2/20/17
 ** Description: Constuctor and method definition for the 
                 building class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "background.hpp"
#include "building.hpp"
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
Building::Building(int y, int x): background(8, 13, y, x) {
  s[0] = "============";
  s[1] = "[++++++++++]";
  s[2] = "[  __   __ ]";
  s[3] = "[ |__| |__|]";
  s[4] = "[ |__| |__|]";
  s[5] = "[    _     ]";
  s[6] = "[   | |    ]";
  s[7] = "|----------|";
}  
/*********************************************************************
 *                      update()
 * Description: updates the Building windows 
 * *******************************************************************/
void Building::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the building on the screen
 * ******************************************************************/
void Building::draw() {
  init_pair(8, COLOR_WHITE, COLOR_RED);
  wattron(img, COLOR_PAIR(8));
  for(int i = 0; i < row; i++) 
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(8));
  update_panels();
  doupdate();
}
/******************************************************************
 *                      Desctructor
 * Description: Destroys the panels and the associated img
 * ****************************************************************/
Building::~Building() {
  del_panel(this->pan);
  delwin(this->img);
}
