#include <ncurses.h>
#include <unistd.h>

WINDOW *create_newwin(int flag, int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main()
{
    WINDOW *my_win, *my_win_f;
    int height, height_f, width, width_f, starty, starty_f, startx, startx_f;

    initscr(); //start ncurses mode
    curs_set(0);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

    wbkgd(stdscr, COLOR_PAIR(1));
    refresh();

    //create text window
    height = 15;
    width = 40;
    starty = ((LINES - height)/2)+5;
    startx = ((COLS - width)/2);
    my_win = create_newwin(1, height, width, starty, startx);
    wattron(my_win, COLOR_PAIR(1));
    mvwprintw(my_win, 2, 16, "%s", "GAME OVER");
    mvwprintw(my_win, 7, 11, "%s", "FINAL SCORE: 10,234");
    wattron(my_win, A_BLINK);
    mvwprintw(my_win, 9, 10, "%s", "THIS IS A NEW HIGH SCORE!");
    wattroff(my_win, A_BLINK);
    wattroff(my_win, COLOR_PAIR(1));
    wrefresh(my_win);

    //create fireworks window
    height_f = 10;
    width_f = 40;
    starty_f = ((LINES - height_f)/2) - 10;
    startx_f = ((COLS - width_f)/2);
    my_win_f = create_newwin(0, height_f, width_f, starty_f, startx_f);
    int i;
    for (i = 0; i < 10; i++){
    	wattron(my_win_f, COLOR_PAIR(2));
    	mvwprintw(my_win_f, 9, 20, ".");
    	wrefresh(my_win_f);
    	usleep(500000);
    	wattroff(my_win_f, COLOR_PAIR(2));
    	werase(my_win_f);
    	wattron(my_win_f,COLOR_PAIR(1)); 
    	mvwprintw(my_win_f, 8, 19, "...");
    	wattroff(my_win_f, COLOR_PAIR(1));
    	wrefresh(my_win_f);
    	usleep(500000);
    	werase(my_win_f);
    	wattron(my_win_f, COLOR_PAIR(4));
    	mvwprintw(my_win_f, 6, 20, ".");
    	mvwprintw(my_win_f, 7, 17, ".     .");
    	wrefresh(my_win_f);
    	usleep(500000);
    	wattroff(my_win_f, COLOR_PAIR(4));
    	werase(my_win_f);
    	wattron(my_win_f, COLOR_PAIR(2));
    	mvwprintw(my_win_f, 4, 20, ".");
    	mvwprintw(my_win_f, 6, 15, ".         .");
    	wrefresh(my_win_f);
    	usleep(500000);
    	wattroff(my_win_f, COLOR_PAIR(2));
    	werase(my_win_f);
    	wattron(my_win_f, COLOR_PAIR(3));
    	mvwprintw(my_win_f, 4, 19, "_\\/_");
    	mvwprintw(my_win_f, 5, 19, " /\\");
    	mvwprintw(my_win_f, 6, 14, "_\\/_     _\\/_");
    	mvwprintw(my_win_f, 7, 14, " /\\       /\\");
    	wrefresh(my_win_f);
    	usleep(500000);
	werase(my_win_f);
    	wattroff(my_win_f, COLOR_PAIR(3));
    }
    
    endwin(); //end ncurses mode
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
				* 				* lines */
        wrefresh(local_win); /* Show that box */
    }
    return local_win;
}
