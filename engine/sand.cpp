/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "background.hpp"
#include "sand.hpp"
#include <ncurses.h>
#include <iostream>
#include <panel.h>
#include <time.h>
#include <string>
#include <time.h>
#include <cstring>
#include <random>
#include <chrono>

/*********************************************************************
 *                      construtor
 * Description: Adds a char array to the base class
 * *******************************************************************/
Sand::Sand(int r, int c, int y, int x): background(r, c, y, x) {
  char xp[] = "x.";
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 g (seed);
  for (int i = 0; i < row; i++) 
  {
    std::string newS;
    s.push_back(newS);
    for (int j = 0; j < col; j++)
    {
      s[i].push_back(xp[g() % 2]);
    }
  }
}  
/*********************************************************************
 *                      update()
 * Description: updates the sand windows 
 * *******************************************************************/
void Sand::update() {
  char xp[] = "x.";
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 g (seed);
  for(int i = 0; i < row; i++)
  {
    for(int j = 0; j < col-1; j++)
    {
      std::swap(s[i].at(j+1), s[i].at(j));
    }
    s[i].at(col-1) = (xp[g() % 2]);
  }
  this->draw();
}
/*********************************************************************
 *                      hide
 * Description: hides the panel
 * ******************************************************************/
void Sand::hide() {
}
/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Sand::draw() {
  init_pair(25, COLOR_YELLOW, COLOR_BLACK);
  wattron(img, COLOR_PAIR(25));
  for(int i = 0; i < row; i++)
  {
    mvwprintw(img, i, 0, "%s", s[i].c_str());
  }
  wattroff(img, COLOR_PAIR(25));
  wrefresh(img);
}
/*********************************************************************
 *                      end
 * Description: Decreases the sand on the screen
 * *******************************************************************/
void Sand::end() {
  for(int i = 0; i < row; i++)
  {
    for(int j = 0; j < s[i].length()-2; j++)
    {
      if(s[i].length() > 1)
      {
        {
          std::swap(s[i].at(j+1), s[i].at(j));
        }
      }
    }
    s[i].erase(s[i].length()-1);
  }
  this->draw();
}

/**********************************************************************
 *                      start
 * Description: Starts the sand on the screen moving to the right
 * *******************************************************************/
void Sand::start() {
  char xp[] = "x..x.x";
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 g (seed);
  for (int i = 0; i < row; i++) 
  {
    for (int j = 0; j < col; j++)
    {
      s[i].push_back(xp[ g() % 6]);
    }
  }
  this->draw();
}
/*********************************************************************
 *                      isFull
 * Description: Returns a bool stating whether or not the object has
 *              finished drawing
 * ******************************************************************/
bool Sand::isFull() {
  if(s[0].length() < col)
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
Sand::~Sand() {
  del_panel(pan);
  delwin(img);
}
