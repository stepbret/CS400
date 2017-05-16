#include <ncurses.h>
#include <cmath>
#include <string.h>
#include <panel.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <random>

#include "engine.hpp"
#include "kelp.hpp"
int main() {

  int row, col;
  initscr();
  cbreak();
  noecho();

  getmaxyx(stdscr, row, col);

  start_color();

  if(!can_change_color){
    printf("Can't Change the color\n");
  }
  
  Engine game(row, col);
  for(int level = 0; level < 3; level++)
  {
    game.load(level);
    game.run(level);
    game.endLevel(level);
  }
  getch();


  endwin();
  return 0;
}

