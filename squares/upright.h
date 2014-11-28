#ifndef __UPRIGHT_SQUARE_H__
#define __UPRIGHT_SQUARE_H__

#include "square.h"

class Xwindow;

class UprightSquare: public Square{

  public:
    UprightSquare(int r, int c, std::string color);
    void remove(int count);
    void draw(Xwindow *window, int x, int y);

};


#endif
