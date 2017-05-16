/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "background.hpp"
#include <ncurses.h>
#include <iostream>
#include <panel.h>
#include <time.h>
#include <stdlib.h>

/**********************************************************************
 *                          Constructor
 * Description: defines the window size that we are using for the background
 * *******************************************************************/
background::background(int r, int c, int y, int x) {
  setRows(r);
  setCols(c);
  setPosY(y);
  setPosX(x);
  img = newwin(r, c, y, x);
  pan = new_panel(img);
}

/**********************************************************************
 *                          SetLength
 * Description: sets the length for the background window size
 * *******************************************************************/
void background::setRows(int r) {
  row = r;
}
/**********************************************************************
 *                          setWidth
 * Description: sets the width for the background
 * *******************************************************************/
void background::setCols(int c) {
  col = c;
}

/**********************************************************************
 *                          setPosY
 * Description: sets the y position
 * *******************************************************************/
void background::setPosY(int y) {
  posY = y;
}

/*********************************************************************
 *                          setPosX
 * Description: sets the x position
 * *******************************************************************/
void background::setPosX(int x) {
  posX = x;
}

/********************************************************************
 *                          getPosY
 * Description: gets the y position
 * *****************************************************************/
int background::getPosY() {
  return posY;
}

/********************************************************************
 *                          getPosX
 * Description: Gets the x position
 * ******************************************************************/
int background::getPosX() {
  return posX;
}
/**********************************************************************
 *                         getLength
 * Description: gets the length of the background that was set
 * *******************************************************************/
int background::getCols() {
  return col;
}

/**********************************************************************
 *                          getWidth
 * Description: gets the width of the background we are using
 * *******************************************************************/
int background::getRows() {
  return row;
}
/*********************************************************************
 *                          isStarting
 * Description: Returns a boolean if the background is starting
 * *******************************************************************/
bool background::isStarting() {
  return this->start;
}
/********************************************************************
 *                          setStarting
 * *****************************************************************/
void background::setStarting(bool s) {
  this->start = s;
}
/********************************************************************
 *                          checkDestroy
 * Description: checks if the background object is off the screen
 *              and returns if it needs to be destoryed
 * ******************************************************************/
bool background::checkDestroy() {
  if (this->posX <= 0 || this->posY <= 0)
  {
    return true;
  }
  return false;
}

void background::refresh() {
  wrefresh(this->img);
}
/********************************************************************
 *                          getPanel
 * Description: Returns the panel
 *******************************************************************/
PANEL* background::getPanel() {
  return this->pan;
}
/********************************************************************
 *                          Destructor
 * Description: Destroys the objects and deletes the panel
 * *****************************************************************/
background::~background() {
}

