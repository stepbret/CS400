/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "background.hpp"
#include "sky.hpp"
#include <ncurses.h>
#include <iostream>
#include <panel.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <cstring>
#include <random>
#include <chrono>


/*********************************************************************
 *                      construtor
 * Description: Adds a char array to the base class
 * *******************************************************************/
Sky::Sky(int r, int c, int y, int x): background(r, c, y, x) {
  char xp[] = "-`~*";
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 g (seed);
  for (int i = 0; i < row; i++) 
  {
    std::string newS;
    s.push_back(newS);
    for (int j = 0; j < col; j++)
    {
      s[i].push_back(xp[g() % 4]);
    }
  }
}
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Sky::update() {
    char xp[] = "-`~*";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g (seed);
    for(int i = 0; i < row; i++)
    {
      for(int j = 0; j < col-1; j++)
      {
        std::swap(s[i].at(j+1), s[i].at(j));
      }
      s[i].at(col-1) = (xp[g() % 4]);
    }
  this->draw();
}

/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Sky::draw() {
  init_pair(26, COLOR_WHITE, COLOR_BLUE);
  wattron(img, COLOR_PAIR(26));
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(26));
  wrefresh(img);
}
/***********************************************************************
 *                      end
 * Description: ends the sky
 * ********************************************************************/
void Sky::end() {
  for(int i = 0; i < row; i++)
  {
    for(int j = 0; j < s[i].length()-1; j++)
    {
      if(s[i].length() > 1)
      {
      std::swap(s[i].at(j+1), s[i].at(j));
      }
    }
    s[i].erase(s[i].end()-1);
  }
  this->draw();
}
/***********************************************************************
 *                      isFull
 * Description: Returns a boolean determining if the objects is done
 *              updating
 * ********************************************************************/
bool Sky::isFull() {
  if(s[0].length() == this->getCols())
  {
    return false;
  }
  else
  {
    return true;
  }
}
/******************************************************************
 *                      Desctructor
 * Description: Destroys the panels and the associated img
 * ****************************************************************/
Sky::~Sky() {
  del_panel(this->pan);
  delwin(this->img);
}
