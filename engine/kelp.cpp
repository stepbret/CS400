/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 2/20/17
 ** Description: Constuctor and method definition for the 
                 building class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "background.hpp"
#include "kelp.hpp"
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
Kelp::Kelp(int y, int x): background(16, 7, y, x) {
  s[0] = "/\\";
  s[1] = "\\k\\";
  s[2] = "/k/";
  s[3] = "\\k\\";
  s[4] = " \\k\\";
  s[5] = " /k/";
  s[6] = "/k/";
  s[7] = "/k/";
  s[8] = "\\k\\";
  s[9] = " \\k\\";
  s[10] = " /k/";
  s[11] = "/k/";
  s[12] = "\\k\\";
  s[13] = "/k/";
  s[14] = "\\k\\";
  s[15] = "/k/";
}  
/*********************************************************************
 *                      update()
 * Description: updates the Building windows 
 * *******************************************************************/
void Kelp::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the building on the screen
 * ******************************************************************/
void Kelp::draw() {
  init_pair(31, COLOR_GREEN, COLOR_BLUE);
  wbkgd(img, COLOR_PAIR(31));
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  doupdate();
}
/************************************************************************
 *                      Desctructor
 * Description: Destroys the object
 * *********************************************************************/
Kelp::~Kelp() {
  del_panel(this->pan);
  delwin(this->img);
}
