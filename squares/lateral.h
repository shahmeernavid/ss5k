#ifndef __LATERAL_SQUARE_H__
#define __LATERAL_SQUARE_H__

#include "square.h"

class Xwindow;

class LateralSquare: public Square{

  public:
    LateralSquare(int r, int c, std::string color);
    int remove(int count = 0);
    void draw(Xwindow *window, int x, int y);

};


#endif
