/**********************************************************************
 ** Author: Brett Stephenson
 ** Date: 2/08/17
 ** Description: Constuctor and method definition for the 
                 engine class, this will run the game
 * ********************************************************************/

#include "engine.hpp"
#include "gameObj.hpp"
#include "cactus.hpp"
#include "quickSand.hpp"
#include "background.hpp"
#include "player.hpp"
#include "rLines.hpp"
#include "pothole.hpp"
#include "building.hpp"
#include "sky.hpp"
#include "sand.hpp"
#include "missle.hpp"
#include "car.hpp"
#include "kelp.hpp"
#include "water.hpp"
#include "pavement.hpp"
#include "whirlpool.hpp"
#include "shark.hpp"
#include "bubbles.hpp"

#include <ncurses.h>
#include <iostream>
#include <panel.h>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <pthread.h>
#include <stdio.h>

/**********************************************************************
 *                          Constructor
 * Description: defines the window size that we are using for the background
 * *******************************************************************/
Engine::Engine(int r, int c) {
  tick = 1;
  levels[0] = "1level.txt";
  levels[1] = "2level.txt";
  levels[2] = "3level.txt";
  jumping = false;
  jumpDir = 15;
  nextLevel = 0;
  starting = false;
  setRow(r);
  setCol(c);

  sand = NULL;
  po = NULL;
  sky = NULL;
  water = NULL;
  pave = NULL;
}
/*********************************************************************
 *                          setRow
 * Description: sets the rows for the engine
 * ******************************************************************/
void Engine::setRow(int r){
  row = r;
}
/********************************************************************
 *                          setCol
 * Description: sets the cols for the engine
 * ******************************************************************/
void Engine::setCol(int c) {
  col = c;
}
/********************************************************************
 *                          addBg
 * Description: adds the pointers to the vectors
 * ******************************************************************/
void Engine::addBg(background* bgPtr){
  bg.push_back(bgPtr);
}

/*********************************************************************
 *                          addGo
 * Description: Adds the game object to the vector
 * ******************************************************************/
void Engine::addGo(GameObj* goPtr) {
  go.push_back(goPtr);
}

/*******************************************************************
 *                          addMissle
 * Description: adds a missle to the array and tracks it
 * ******************************************************************/
void Engine::addMo(Missle* m) {
  mo.push_back(m);
}
/* *******************************************************************
 *                          getBgPtr
 * Description: Returns the vector with the pointers
 * *******************************************************************/
background* Engine::getBgPtr() {
  //return *bgPtr
}

/********************************************************************
 *                          getGoPtr()
 * Description: Returns the vector with pointers to GameObj
 * ****************************************************************/
GameObj* Engine::getGoPtr() {
  //return *goPtr;
}
/*******************************************************************
 *                          load
 * Description: draws the objects and backgrounds onto the screen
 * *****************************************************************/
void Engine::load(int level) {

  if(level == 0)
  {
    // Make the objects
    Cactus *c1 = new Cactus((this->row - this->row/4) - 8, col-17);
    QuickSand *qs1 = new QuickSand((row-row/4 - 1), col-30); 
    sand = new Sand(row/4, col, (row-row/4), 0);
    sky = new Sky(row/4, col, 0, 0);
    
    // Make the player object
    po = new Player((row-row/4) - 3, 0);
    po->setLevel(level);

    // Add all of the objects to the game
    this->addGo(qs1);
    this->addGo(c1);

    //Draw the objects
    for(int i = 0; i < go.size(); i++) 
      go[i]->draw();

    sky->draw();
    po->draw();
    sand->draw();
  }
  
  // If it's the second level
  if(level == 1)
  {
    Pothole *p1 = new Pothole((row-row/4) - 1, col - 30);
    Car *c = new Car((row-row/4) - 3, col- 12);
    pave = new Pavement(row/4, col, (row-row/4), 0);

    this->addGo(p1);
    this->addGo(c);
    po->setLevel(level);

    for(int i = 0; i < go.size(); i++)
      go[i]->draw();
    
    // Draw everything
    sky->draw();
    po->draw();
    pave->draw();
  } 
  //if it's the third level
  if(level == 2)
  {
    Sand *s = new Sand(row/4, col, (row-row/4), 0);
    Water *wa = new Water(row-row/4, col, 0, 0);
    Whirlpool *wh = new Whirlpool(row-row/4 - 3, col-30);
    Shark *shark = new Shark(row-row/4 - 6, col-15);
    Bubbles *bub = new Bubbles(30, col-20);

    this->addGo(wh);
    this->addGo(shark);
    this->addBg(bub);
    
    po->setLevel(level);
    sand = s;
    water = wa;

    for(int i = 0; i < go.size(); i++)
      go[i]->draw();
    
    // Draw everything
    water->draw();
    bub->draw();
    sand->draw();
    po->draw();
  }
  refresh(); 
}
/******************************************************************
 *                          setStart
 * Descritpion: determines if the sand is done loading
 * *****************************************************************/
void Engine::updateScenery(int level) {

  //if its the first level, do nothing
  if(level == 0){
    sand->update();
    sky->update();
  }

  //if its the second level
  if(level == 1){
    sky->update();
    pave->update();
  }

  //if it is the last level
  if(level == 2){
    sand->update();
    water->refresh();
  }
}
/********************************************************************
 *                          updateObjs()
 * Description: update the objects in the vector
 * *****************************************************************/
void Engine::updateObjs(int level) {

    // Updates the background scenery sky/sand/water/pavement
    this->updateScenery(level); 

    //updates the background objs, buildings/ rlines etc
    if(bg.size() > 0)
    {
      for(int i = 0; i < bg.size(); i++)
      {
        bg[i]->update();
        if(bg[i]->checkDestroy())
        {
          delete bg[i];
          bg.erase(bg.begin() + i);
        }
      }
    }

    //redraws the player for updates
    po->draw();

    // updates the game objects, sandpits/cars/sharks etc
    for(int i = 0; i < go.size(); i++)
    {
      go[i]->update();
      if(go[i]->checkDestroy())
      {
         delete go[i];
         go.erase(go.begin() + i);
      }
      else
      {
        top_panel(go[i]->getPanel());
      }
    }
    // Update the missles
    if(mo.size() > 0)
    {
      for(int i = 0; i < mo.size(); i++)
      {
        mo[i]->update();
        if(mo[i]->getPosX() == this->row)
        {
          delete mo[i];
          mo.erase(mo.begin() + i);
        }
      }
    }
    // Check to see if the player is jumping
    if(jumping)
    {
      if(jumpDir >= 0)
      {
        po->jumpUp();
        --jumpDir;
        if(jumpDir == 1)
        {
          jumpDir = -16;
        }
      } 
      else 
      {
        po->jumpDown();
        ++jumpDir;
        if(jumpDir == -1)
        {
          jumpDir = 15;
          jumping = false;
        }
      }
    }
    else
    {
      po->update();
    }
}

/****************************************************************************
 *                      endLevel
 * Description: Ends the level and deletes all of the objects being pointed to
 * * *************************************************************************/
void Engine::endLevel(int level) {
  if (level == 0)
  {
    delete sand;
    for(int i = 0; i < go.size(); i++){
      if(go[i] != NULL)
        delete go[i];
    }
    go.clear();
    for(int i = 0; i < bg.size(); i++)
    {
      if(bg[i] != NULL)
        delete bg[i];
    }
    bg.clear();
  }
  if (level == 1) 
  {
    delete pave;
    delete sky;
    for(int i = 0; i < go.size(); i++)
    {
      if(go[i] != NULL)
        delete go[i];
    }
    go.clear();
    for(int i = 0; i < bg.size(); i++)
    {
      if(bg[i] != NULL)
        delete bg[i];
    }
    bg.clear();
  }
  if (level == 2) 
  {
    delete sand;
    delete po;
    delete water;
    for(int i = 0; i < go.size(); i++)
    {
      if(go[i] != NULL)
        delete go[i];
    }
    go.clear();
    for(int i = 0; i < bg.size(); i++)
    {
      if(bg[i] != NULL)
        delete bg[i];
    }
    bg.clear();
  }
}

/*******************************************************************
 *                          getCoords
 * Description: This set of functions is meant to be called inside
 *              a mutex lock 
 * *****************************************************************/
void Engine::getCoords(int x, int y) {
  po->setPosX(x);
  po->setPosY(y);
  po->draw();
}

int Engine::setxCoord(){
  return po->getPosX();
}

int Engine::setyCoord() {
  return po->getPosY();
}
/********************************************************************
 *                          run
 * Description: Runs the game, updates each object in the vectors to
 *              move forward
 * ******************************************************************/
void Engine::run(int level) {
  using namespace std::chrono;
  std::ifstream fp(levels[level]);
  FILE *fo;
  bool collide = false;
  bool endOfLevel = false;
  start_color();
  
  // Get the start time 
  steady_clock::time_point startTime = steady_clock::now();
  while(!collide && !endOfLevel) 
  {
    // Get the current time to compare to start time
    // If the current time is half a second after the start time, update everything
    steady_clock::time_point currentTime = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(currentTime - startTime);
    if(time_span.count() >= 0.060)
    {
      this->updateObjs(level);
      tick++;
      collide = this->detectPlayerCollisions();
      this->detectMissleCollisions();
      if(tick % 20 == 0)
      {
        endOfLevel = this->getObs(fp);
        this->setScenery(level);
      }
      // Reset the timer
      startTime = steady_clock::now();
    }
    refresh();
    this->localcheckInput();
  }
}
/********************************************************************
 *                          detectMissleCollision
 * Description: Detects collision between missles and 
 * *****************************************************************/
bool Engine::detectMissleCollisions() {
  for(int i = 0; i < mo.size(); i++)
  {
    GameObj *goPtr1 = mo[i];
    for(int j = 0; j < go.size(); j++)
    {
      GameObj *goPtr2 = go[j];
      // Get the position of object 1 and length in X
      int startX1 = goPtr1->getPosX();
      int endX1 = startX1 + goPtr1->getCols();

      // Get the y position of object 1
      int startY1 = goPtr1->getPosY();
      int endY1 = startY1 + goPtr1->getRows();

      // Get the x position of object 2
      int startX2 = goPtr2->getPosX();
      int endX2 = startX2 + goPtr2->getCols();

      //Get the y position of Object 2
      int startY2 = goPtr2->getPosY();
      int endY2 = startY2 + goPtr2->getRows();
      
      //0    startX1    endx1  startX2     endX2 100
      //startY1              start2_ _ _ _ _
      //                          |         |
      //   X=>                    |         |
      //                     endY2|_ _ _ _ _|
      //
      //100                                       MAX
      if(endX1 >= startX2 && startY1 >= startY2)
      {
        if(startX1 >= endX2)
        {
         return false;
        } 

        // I realize the only this works is because no two objects 
        // will exist in the same space
        mo.erase(mo.begin() + i);
        go.erase(go.begin() + j);
        delete goPtr1;
        delete goPtr2;
        return true;
      }
    }
  }
}
  
/********************************************************************
 *                          detectPlayerCollions
 * Description: Will detect a collision between two game objects
 * *****************************************************************/
bool Engine::detectPlayerCollisions() {
  GameObj *goPtr1 = po;
  for(int i = 0; i < go.size(); i++)
  {
    GameObj *goPtr2 = go[i];
    // Get the position of object 1 and length in X
    int startX1 = goPtr1->getPosX();
    int endX1 = startX1 + goPtr1->getCols();

    // Get the y position of object 1
    int startY1 = goPtr1->getPosY();
    int endY1 = startY1 + goPtr1->getRows();

    // Get the x position of object 2
    int startX2 = goPtr2->getPosX();
    int endX2 = startX2 + goPtr2->getCols();

    //Get the y position of Object 2
    int startY2 = goPtr2->getPosY();
    int endY2 = startY2 + goPtr2->getRows();
    
    //0    startX1    endx1  startX2     endX2 100
    //startY1  _ _ _ _ _   start2_ _ _ _ _
    //        |          |      |         |
    //        |          |      |         |
    //endY1   |_ _ _ _ _ | endY2|_ _ _ _ _|
    //
    //100                                       MAX
    if(endX1 >= startX2 && endY1 >= startY2)
    {
      if(startX1 >= endX2)
      {
       return false;
      } 
      return true;
    }
  }
}

/*********************************************************************
 *                          getObs
 * Description: Read in the obstacles for the level
 * Params: string pointing to the file of the level
 * Output: adds the object to the objects vector
 * *******************************************************************/
bool Engine::getObs(std::ifstream &fp) {
  std::string object;
  getline(fp, object);
  if(object == "cactus")
  {
    Cactus *cact = new Cactus((row - row/4) - 8, col - 12);
    cact->draw();
    this->addGo(cact);
  }
  if(object == "quicksand")
  {
    QuickSand *qs = new QuickSand((row-row/4) - 1, col - 12);
    qs->draw();
    this->addGo(qs);
  }
  if(object == "pothole")
  {
    Pothole *p = new Pothole((row-row/4) - 1, col-14);
    p->draw();
    this->addGo(p);
  }
  if(object == "car")
  {
    Car *c = new Car((row-row/4) - 3, col-14);
    c->draw();
    this->addGo(c);
  }
  if(object == "shark")
  {
    Shark *shark = new Shark(row-row/4 - 6, col-15);
    shark->draw();
    this->addGo(shark);
  }
  if(object == "whirlpool")
  {
    Whirlpool *wh = new Whirlpool(row-row/4 - 2, col-30);
    wh->draw();
    this->addGo(wh);
  }
  if(fp.eof())
  {
    fp.close();
    return true;
  }
  return false;
}
/*******************************************************************
 *                          checkInput
 * Description: Checks for the input and returns the char
 * ****************************************************************/
char Engine::checkInput() {
  nodelay(stdscr, true);
  char key = getch();
  if(key == 'a')
    return 'a';
  if(key == 'd')
    return 'd';
  if(key == ' ')
    return ' ';
  if(key == 'f')
    return 'f';
  if(key == 'q')
    return 'q';
}
 /*******************************************************************
  *                          localcheckInput
  * Description: Checks for the input
  * ****************************************************************/
 void Engine::localcheckInput() {
   nodelay(stdscr, true);
   char key = getch();
   if (key == 'w')
   {
     if(jumping)
     {
     return;
     }
     po->jumpUp();
     jumping = true;
   }
   if (key == 'd')
   {
     po->forward();
   }
   if (key == 'a')
   {
     po->backward();
   }
   if(key == 's')
   {
     po->jumpDown();
   }
   if(key == ' ') 
   {
     Missle *m = new Missle(po->getPosY() + 1, po->getPosX() + 8);
     m->draw();
     this->addMo(m);
   }
 }
/*****************************************************************
 *                      getShoot
 * ***************************************************************/
void Engine::getShoot(int shoot) {
  if(shoot == 1)
  {
    Missle *m = new Missle(po->getPosY() + 1, po->getPosX() + 10);
    m->draw();
    this->addMo(m);
  }
}
/****************************************************************
 *                      setScenery
 * Description: adds some background objects to the scenery
 * **************************************************************/
void Engine::setScenery(int level) {
  if (level == 1) 
  {
    rLines *r = new rLines(row-row/4, col-7);
    r->draw();
    this->addBg(r);
    
    Building *b = new Building(row-row/4 - 8, col - 10);
    b->draw();
    this->addBg(b);
  }
  if (level == 2) 
  {
    Kelp *k = new Kelp(row-row/4 - 16, col - 7);
    Bubbles *b = new Bubbles(row-row/4 - 7, col - 6);
    k->draw();
    b->draw();
    this->addBg(b);
    this->addBg(k);
  }
}

