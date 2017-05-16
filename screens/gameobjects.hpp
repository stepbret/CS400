#include "screens.hpp"
#include <vector>

namespace gameobjects
{
    //set up for load screen
    //set up vector containing titlebox, tankwindow
    std::vector<GameWindow *> loadobj;
    TitleTextBox titleBox(15, 40, ((COLS - 40)/2), (((LINES - 15)/2) - 10), 1);
    TankLoadWindow tankLoadWin(10, 40, ((COLS - 40)/2), (((LINES - 10)/2) + 5), 0);
    loadobj.push_back(&titleBox);
    loadobj.push_back(&tankLoadWin);
    //set up static load screen (no user input)
    StaticScreen loadScreen(loadobj);
/*
    //set up vector of keys for menu screen
    std::vector<int> menukeys;
    menukeys.push_back('p');
    menukeys.push_back('P');
    menukeys.push_back('q');
    menukeys.push_back('Q');
    menukeys.push_back('t');
    menukeys.push_back('T');
    
    //set up vector containing menubox game object
    std::vector<GameWindow *> gameobj;
    MenuTextBox menuBox(20, 40, ((COLS/2)-20), ((LINES/2)-10), 1);
    gameobj.push_back(&menuBox);
    
    //set up interactive menu screen
    InteractScreen menuScreen(gameobj, 0, menukeys);
*/
}
