/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include "quickSand.hpp"

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
QuickSand::QuickSand(int y, int x): GameObj(6, 9, y, x) {
  s[0]="         "; 
  s[1]="\\______/";
  s[2]="x\\\\////x";
  s[3]=".\\\\///x.";
  s[4]=".x\\//x.x";
  s[5]="x.\\/.x.x";
  
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void QuickSand::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void QuickSand::draw() {
  wattron(img, COLOR_PAIR(25) | A_BOLD);
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(25));
  show_panel(pan);
  update_panels();
  doupdate();
}
/*****************************************************************
 *                      Desctructor
 * **************************************************************/
QuickSand::~QuickSand(){
  del_panel(this->pan);
  delwin(this->img);
}
