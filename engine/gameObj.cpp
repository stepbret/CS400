/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include <ncurses.h>
#include <iostream>
#include <panel.h>
#include <time.h>
#include <stdlib.h>

/**********************************************************************
 *                          Constructor
 * Description: defines the window size that we are using for the background
 * *******************************************************************/
GameObj::GameObj(int r, int c, int y, int x) {
  img = newwin(r, c, y, x);
  pan = new_panel(img);
  setRows(r);
  setCols(c);
  setPosY(y);
  setPosX(x);
}

/**********************************************************************
 *                          SetLength
 * Description: sets the length for the background window size
 * *******************************************************************/
void GameObj::setRows(int r) {
  row = r;
}
/**********************************************************************
 *                          setWidth
 * Description: sets the width for the background
 * *******************************************************************/
void GameObj::setCols(int c) {
  col = c;
}

/**********************************************************************
 *                          setPosY
 * Description: sets the y position
 * *******************************************************************/
void GameObj::setPosY(int y) {
  posY = y;
}

/*********************************************************************
 *                          setPosX
 * Description: sets the x position
 * *******************************************************************/
void GameObj::setPosX(int x) {
  posX = x;
}

/********************************************************************
 *                          getPosY
 * Description: gets the y position
 * *****************************************************************/
int GameObj::getPosY() {
  return posY;
}

/********************************************************************
 *                          getPosX
 * Description: Gets the x position
 * ******************************************************************/
int GameObj::getPosX() {
  return posX;
}
/**********************************************************************
 *                         getLength
 * Description: gets the length of the background that was set
 * *******************************************************************/
int GameObj::getCols() {
  return col;
}

/**********************************************************************
 *                          getWidth
 * Description: gets the width of the background we are using
 * *******************************************************************/
int GameObj::getRows() {
  return row;
}
/*********************************************************************
 *                          getWindow
 * Description: Returns the window for the derived obj
 * *******************************************************************/
WINDOW* GameObj::getWin() {
  return img;
}
/*********************************************************************
 *                          getPanel
 * Description: Returns the panel for the derived obj
 * *******************************************************************/
PANEL* GameObj::getPanel() {
  return this->pan;
}
/********************************************************************
 *                          Destroy
 * Description: Deletes itself if it runs out of space
 * ******************************************************************/
bool GameObj::checkDestroy() {
  if(this->posX <= 0)
  {
    this->hide(); 
    return true;
  }
  return false;
}
/***********************************************************************
 *                              Hide
 * Description: hides the panel
 * **********************************************************************/
void GameObj::hide() {
  hide_panel(this->pan);
}

/*****************************************************************
 *                          Desctructor
 * Description: Destroys the object
 * **************************************************************/
GameObj::~GameObj(){
}
