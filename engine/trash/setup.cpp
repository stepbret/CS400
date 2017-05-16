#include <ncurses.h>
#include <cmath>
#include <string.h>
#include <panel.h>
#include <stdlib.h>
#include <time.h>

#include "../background.hpp"
//#include "sand.hpp"
//#include "sky.hpp"
/*#include "gameObj.hpp"
#include "cactus.hpp"
#include "quickSand.hpp"
#include "engine.hpp"
#include "player.hpp"*/
#include "pavement.hpp"
//#include "rLines.hpp"

int main() {
  srand(time(NULL));

  int row, col;
  initscr();
  cbreak();
  noecho();

  getmaxyx(stdscr, row, col);

  start_color();

  if(!can_change_color){
    printf("Can't Change the color\n");
  }
  
  Pavement p(row/4, col, (row - row/4), 0);
  p.draw();
  for(int i = 0; i < 10; i++){
    p.start();
    p.draw();
    getch();
    refresh();
  }
  for(int i = 0; i < 10; i++){
    p.end();
    getch();
    refresh();
  }

  /*Sky sk(row/4, col, 0, 0);
  Cactus c1((row - row/4) - 8, col-17);
  QuickSand qs1((row-row/4 - 1), col-30);
  Cactus *cPtr = &c1;
  rLines r(2, 5, (row - row/4), col);
  

  Player p((row-row/4) - 3, 0);*/

  /*
  game.addBg(&sk);
  game.addBg(&pa);
  game.addBg(&r);
  game.addGo(&qs1);
  game.addGo(cPtr);
  game.addPo(&p);
  */

  refresh();
  endwin();
  

  return 0;
}

