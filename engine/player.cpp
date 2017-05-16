/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 1/21/17
 ** Description: Constuctor and method definition for the 
                 background class, objects will be able to be placed
                 in the background
 * ********************************************************************/

#include "gameObj.hpp"
#include "player.hpp"

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
Player::Player(int y, int x): GameObj(3, 11, y, x) {
  s[0] = "   ___     ";
  s[1] = " _/XXX\\--o ";
  s[2] = "\\O-O-O-O-/ ";
  level = 0;
}  
/*********************************************************************
 *                      forward()
 * Description: Moves the player forward 
 * *******************************************************************/
void Player::forward() {
  this->posX++;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}
/*********************************************************************
 *                      backward()
 * Description: updates the sand windows 
 * *******************************************************************/
void Player::backward() {
  this->posX--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}

/*********************************************************************
 *                      jumpUp
 * Description: Jumps the tank
 * *******************************************************************/
void Player::jumpUp() {
  this->posY--;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}
/*********************************************************************
 *                      jumpDown
 * Description: Handles the downward movement of the tank
 * ******************************************************************/
void Player::jumpDown() {
  this->posY++;
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}
/********************************************************************
 *                      draw
 * Description: Draws the sand on the screen
 * ******************************************************************/
void Player::draw() {
  if(level == 2)
  {
    init_pair(19, COLOR_MAGENTA, COLOR_BLUE);
    wattron(img, COLOR_PAIR(19) | A_BOLD);
    for(int i = 0; i < row; i++)
      {
        mvwprintw(img, i, 0, "%s", s[i].c_str());
      }
    wattroff(img, COLOR_PAIR(19));
  }
  else
  {
    init_pair(30, COLOR_MAGENTA, COLOR_BLACK);
    wattron(img, COLOR_PAIR(30) | A_BOLD);
    for(int i = 0; i < row; i++)
      {
        mvwprintw(img, i, 0, "%s", s[i].c_str());
      }
    wattroff(img, COLOR_PAIR(30));
  }
  show_panel(pan);
  update_panels();
  doupdate();
}
/******************************************************************
 *                      update
 * Description: Updates the player model
 * ****************************************************************/
void Player::update() {
  move_panel(pan, this->posY, this->posX);
  update_panels();
  doupdate();
}
/******************************************************************
 *                      Desctructor
 * Description: Destroys the panels and the associated img
 * ****************************************************************/
Player::~Player() {
  del_panel(this->pan);
  delwin(this->img);
}

/**************************************************************8
 *                      setLevel
 * ***********************************************************/
void Player::setLevel(int lev){
  level = lev;
}
