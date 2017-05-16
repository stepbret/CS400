/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "background.hpp"
#include "water.hpp"
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
Water::Water(int r, int c, int y, int x): background(r, c, y, x) {
  for(int i = 0; i < 4; i++)
  {
    std::string newS;
    s.push_back(newS);
    for(int j = 0; j < col; j++)
    {
      s[i].push_back('o');
    }
  }
  for (int i = 4; i < row; i++) 
  {
    std::string newS;
    s.push_back(newS);
    for (int j = 0; j < col; j++)
    {
      s[i].push_back('~');
    }
  }
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Water::update() {
  top_panel(pan);
  bottom_panel(pan);
}

bool Water::isFull() {
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Water::draw() {
  init_pair(13, COLOR_WHITE, COLOR_BLUE);
  wattron(img, COLOR_PAIR(13));
  for(int i = 0; i < 4; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(13));
  init_pair(5, COLOR_CYAN, COLOR_BLUE);
  wattron(img, COLOR_PAIR(5));
  for(int i = 4; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(5));
  wrefresh(img);
  update_panels();
  doupdate();
}

/******************************************************************
 *                      Desctructor
 * Description: Destroys the panels and the associated img
 * ****************************************************************/
Water::~Water() {
  del_panel(this->pan);
  delwin(this->img);
}
