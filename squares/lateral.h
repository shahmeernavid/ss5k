#ifndef __LATERAL_SQUARE_H__
#define __LATERAL_SQUARE_H__

#include "square.h"

class Xwindow;

class LateralSquare: public Square{

  public:
    LateralSquare(int r, int c, std::string color);
    void remove(int count);
    void draw(Xwindow *window, int x, int y);

};


#endif
