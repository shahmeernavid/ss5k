#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "textdisplay.h"
#include "window.h"
#include "../grid.h"

class Display {

    Grid *theGrid;
    TextDisplay *td;
    Xwindow *w;
  public:
    Display(Grid *theGrid);
    notify();
};

#endif
