#ifndef __UNSTABLE_SQUARE_H__
#define __UNSTABLE_SQUARE_H__

#include "square.h"

class Xwindow;

class UnstableSquare: public Square{

  public:
    UnstableSquare(int r, int c, std::string color);
    int remove(int count = 0);
    void draw(Xwindow *window, int x, int y);

};


#endif
