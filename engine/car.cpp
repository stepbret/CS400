/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include "car.hpp"

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
Car::Car(int y, int x): GameObj(3, 15, y, x) {
  s[0]="    _____      ";
  s[1]=" __/  |  \\___ ";
  s[2]="|_/0\\___/0\\_|";
  
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Car::update() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Car::draw() {
  init_pair(11, COLOR_MAGENTA, COLOR_BLACK);
  wattron(img, COLOR_PAIR(11));
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(11));
  show_panel(pan);
  update_panels();
  doupdate();
}
/********************************************************************
 *                          Destructor
 * Description: destroys the object and associated panels
 * ******************************************************************/
Car::~Car() {
  del_panel(this->pan);
  delwin(this->img);
}
