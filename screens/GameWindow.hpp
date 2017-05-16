#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <ncurses.h>
#include <panel.h>

class GameWindow
{
    protected:
	int height;
	int width;
	int starty;
	int startx;
	int boxflag;
//	int panelFlag;
	WINDOW *win;
	void createWindow()
	{
	    win = newwin(height, width, starty, startx);
	    if (boxflag == 1)
	    {
		box(win, 0, 0);/*0, 0 gives default characters 
				for vertical and horizontal 
				lines of box*/
		wrefresh(win);
	    }
	}

    public:
	//default constructor
	GameWindow(){height=0;width=0;starty=0;startx=0;boxflag=0;}	

	//constructor
	GameWindow(int ht, int wd, int sx, int sy, int bf);

	//setter function: set height
	void setHeight(int ht);

	//setter function: set width
	void setWidth(int wd);

	//setter function: set starty
	void setStartY(int sy);

	//setter function: set startx
	void setStartX(int sx);

	//setter function: set boxflag
	void setBoxFlag(int bf);

	//getter function: get height
	int getHeight();

	//getter function: get width
	int getWidth();

	//getter function: get starty
	int getStartY();

	//getter function: get startx
	int getStartX();

	//getter function: get boxflag
	int getBoxflag() const;

	//getter function: get WINDOW *win;
	WINDOW *getWin();

	//method to clear window
	void clearWindow(){werase(win);}

	//virtual destructor
	virtual ~GameWindow(){}

	//pure virtual function: set up screen
	virtual void setupWindow() const = 0;
};

#endif
