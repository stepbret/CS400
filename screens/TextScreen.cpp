#include "TextScreen.hpp"
#include <ncurses.h>
#include <string>

void TextScreen::setupWindow() const
{
    init_pair(4, COLOR_WHITE, COLOR_CYAN);
    if (this->getBoxflag() == 1)
        box(win, 0, 0);
    wattron(win, COLOR_PAIR(4));
    wbkgd(win, COLOR_PAIR(4));
    mvwprintw(win, xoffset, yoffset, textStr.c_str());
    wattroff(win, COLOR_PAIR(4));
}
/********************************************************
 * setter method for textStr attribute			*
 *******************************************************/
void TextScreen::setString(std::string str)
{
    textStr = str;
}
/********************************************************
 * getter method for textStr attribute			*
 *******************************************************/
std::string TextScreen::getString()
{
    return textStr;
}
/********************************************************
 * setter method for xoffset attribute			*
 *******************************************************/
void TextScreen::setXOffset(int xoff)
{
    xoffset = xoff;
}
/********************************************************
 * getter method for xoffset attribute			*
 *******************************************************/
int TextScreen::getXOffset()
{
    return xoffset;
}
/********************************************************
 * setter method for yoffset attribute			*
 *******************************************************/
void TextScreen::setYOffset(int yoff)
{
    yoffset = yoff;
}
/********************************************************
 * getter method for yoffset attribute			*
 *******************************************************/
int TextScreen::getYOffset()
{
    return yoffset;
}	
