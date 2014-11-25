#ifndef __BASIC_SQUARE_H__
#define __BASIC_SQUARE_H__

#include "square.h"
#include "../display/window.h"

class BasicSquare: public Square{

  public:
    BasicSquare(int r, int c, std::string color);
    void draw(Xwindow *window, int x, int y);

};


#endif
