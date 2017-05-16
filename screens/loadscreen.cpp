#include <ncurses.h>
#include <unistd.h>
#include <ctime>

WINDOW *create_newwin(int flag, int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{
    WINDOW *my_win, *my_tank;
    int i, startx, startx_t, starty, starty_t, width, width_t, height, height_t;
 
    initscr(); /* Start curses mode */
    curs_set(0);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_MAGENTA);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
    refresh();   
 
    height = 15;
    width = 40;
    starty = ((LINES - height) / 2) - 10; /* Calculating for a center placement */
    startx = (COLS - width) / 2; /* of the window */

    //create title window
    my_win = create_newwin(1, height, width, starty, startx);
    wattron(my_win, COLOR_PAIR(1));
    wattron(my_win, A_BOLD);
    mvwprintw(my_win, 2, 16, "%s", "TANK RUN");
    wattroff(my_win, A_BOLD);
    mvwprintw(my_win, 5, 20, "%s", "by");
    mvwprintw(my_win, 7, 13, "%s", "Jason McAnally");
    mvwprintw(my_win, 8, 12, "%s", "Brittney McInnis");
    mvwprintw(my_win, 9, 12, "%s", "Brett Stephenson");
    wattroff(my_win, COLOR_PAIR(1));
    wrefresh(my_win);

    //create tank window
    height_t = 10;
    width_t = 40;
    starty_t = ((LINES - height_t)/2) + 5;
    startx_t = (COLS - width_t)/2;
    my_tank = create_newwin(0, height_t, width_t, starty_t, startx_t);
    wattron(my_tank, A_BOLD);
    wattron(my_tank, COLOR_PAIR(2));
    mvwprintw(my_tank, 3, 14, "%s", "   U   ");
    wattroff(my_tank, COLOR_PAIR(2));
    wattron(my_tank, COLOR_PAIR(3));
    mvwprintw(my_tank, 3, 21, "%s", "--o");
    mvwprintw(my_tank, 4, 10, "%s", "____");
    wattroff(my_tank, COLOR_PAIR(3)); 
    wattron(my_tank, COLOR_PAIR(2));
    mvwprintw(my_tank, 4, 14, "%s", "       ");
    wattroff(my_tank, COLOR_PAIR(2));
    wattron(my_tank, COLOR_PAIR(3));
    mvwprintw(my_tank, 4, 21, "%s", "____");
    mvwprintw(my_tank, 5, 10, "%s", "\\ O O O O O O /");
    wattroff(my_tank, COLOR_PAIR(3)); 
    wattroff(my_tank, A_BOLD);
    wrefresh(my_tank);

    attron(COLOR_PAIR(1));
    attron(A_BLINK);
    mvprintw(30, 30, "%s", "The game is loading . . .");
    refresh();
    attroff(COLOR_PAIR(1));
    attroff(A_BLINK);

    for (i=0; i < 9; i++)
    {
	wattron(my_tank, COLOR_PAIR(4));
        mvwprintw(my_tank, 3, 26, "*");
        wrefresh(my_tank);
        usleep(500000);
        mvwprintw(my_tank, 3, 26, " ");
        wrefresh(my_tank);
        mvwprintw(my_tank, 3, 29, "*");
        wrefresh(my_tank);
        usleep(500000);
        mvwprintw(my_tank, 3, 29, " ");
        wrefresh(my_tank);
        mvwprintw(my_tank, 3, 32, "*");
        wrefresh(my_tank);
        usleep(500000);
        mvwprintw(my_tank, 3, 32, " ");
        wrefresh(my_tank);
	wattroff(my_tank, COLOR_PAIR(4));
	wattron(my_tank, COLOR_PAIR(5));
        mvwprintw(my_tank, 3, 33, "_\\/_");	
        mvwprintw(my_tank, 4, 33, " /\\ ");
        wrefresh(my_tank);
	usleep(500000);
        mvwprintw(my_tank, 3, 33, "    ");	
        mvwprintw(my_tank, 4, 33, "    ");
        wrefresh(my_tank);
	attroff(COLOR_PAIR(5));
    }

    endwin(); /* End curses mode */
    return 0;
}

WINDOW *create_newwin(int flag, int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    if (flag == 1)
    {
        box(local_win, 0 , 0); /* 0, 0 gives default characters
				* for the vertical and horizontal
				* lines */
        wrefresh(local_win); /* Show that box */
    }
    return local_win;
}

