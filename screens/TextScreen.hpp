#ifndef TEXTSCREEN_HPP
#define TEXTSCREEN_HPP

#include "GameWindow.hpp"
#include <string>

class TextScreen: public GameWindow
{
    private:
	std::string textStr;
	int xoffset; //x offset to start writing string
	int yoffset; //y offset to start writing string
    public:
	//constructor
	TextScreen(int ht, int wd, int sx, int sy, int bf, std::string str, int xoff, int yoff):GameWindow(ht, wd, sx, sy, bf)
	{
	    xoffset = xoff;
	    yoffset = yoff;
	    textStr = str;
	}
    virtual void setupWindow() const;
    //setter method for textStr
    void setString(std::string str);
    //getter method for textStr
    std::string getString();
    //setter method for xoffset
    void setXOffset(int xoff);
    //getter method for xoffset
    int getXOffset();
    //setter method for yoffset
    void setYOffset(int yoff);
    //getter method for yoffset
    int getYOffset();
};

#endif 
