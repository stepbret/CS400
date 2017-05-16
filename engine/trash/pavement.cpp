/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 2/20/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "../background.hpp"
#include "pavement.hpp"
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
Pavement::Pavement(int r, int c, int y, int x): Background(r, c, y, x) {
  char xp[] = "=";
  for (int i = 0; i < row; i++) 
  {
    std::string newS;
    s.push_back(newS);
    for(int j = 0; j < 3; j++)
    {
      s[i].push_back(xp[0]);
    }
  }
  //this->start();
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Pavement::update() {
  this->draw();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Pavement::draw() {
  char tmp[col+1];
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, col - s[i].length(),  "%s", s[i].c_str());
  }
  wrefresh(img);
}
/**********************************************************************
 *                      start
 * Description: Starts the pavement rolling onto the screen
 * *******************************************************************/
void Pavement::start() {
  char xp[] = "=";
  for (int i = 0; i < row; i++) 
  {
    s[i]+="=";
  }
  this->draw();
}
/*********************************************************************
 *                      end
 * Description: Ends the pavement
 * *******************************************************************/
void Pavement::end() {
  if(s[0].length() >= this->getCols())
  {
    for (int i = 0; i < row; i++) 
    {
      s[i].erase(s[i].end() - 1);
    }
  }
  this->draw();
}
/*********************************************************************
 *                      isFull
 * ******************************************************************/
bool Pavement::isFull() {
  if(s[0].length() <= this->getCols())
  {
    return false;
  }
  else
  {
    return true;
  }
}
