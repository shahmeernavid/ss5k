#ifndef __GAME_DISPLAY_H__
#define __GAME_DISPLAY_H__
#include <iostream>
#include <string>
#include "window.h"
#include "../grid.h"

class GameDisplay {

    Grid *theGrid;
    Xwindow *w;
    std::ostream& out; 

    void updateTextDisplay();
    void updateWindowDisplay();

  public:
    GameDisplay(Grid *theGrid);
    void update();
    void output(std::string t);
};

#endif
