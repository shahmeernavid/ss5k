#ifndef __GAME_DISPLAY_H__
#define __GAME_DISPLAY_H__
#include <iostream>
#include <string>
#include "window.h"
#include "../grid.h"
#include "../scoreboard.h"

class Game;

class GameDisplay {

    Game* game;
    Xwindow *w;
    std::ostream& out;

    void updateTextDisplay();
    void updateWindowDisplay();

  public:
    GameDisplay(Game *game, std::ostream& out);
    ~GameDisplay(); 
    void update();
    void output(std::string t);
    void createWindow();
};

#endif
