#ifndef __UNSTABLE_SQUARE_H__
#define __UNSTABLE_SQUARE_H__

#include "square.h"

class Xwindow;

class UnstableSquare: public Square{

  public:
    UnstableSquare(int r, int c, std::string color);
    void remove(int count);
    void draw(Xwindow *window, int x, int y);

};


#endif
