#ifndef __GAME_DISPLAY_H__
#define __GAME_DISPLAY_H__
#include <iostream>
#include <string>
#include "window.h"
#include "../grid.h"
#include "../scoreboard.h"

class GameDisplay {

    Grid *theGrid;
    ScoreBoard *sb;
    Xwindow *w;
    std::ostream *out; 

    void updateTextDisplay();
    void updateWindowDisplay();

  public:
    GameDisplay(Grid *theGrid, ScoreBoard *sb);
    void update();
    void output(std::string t);
    void setWindow(Xwindow *w);
};

#endif
