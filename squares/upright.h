#ifndef __UPRIGHT_SQUARE_H__
#define __UPRIGHT_SQUARE_H__

#include "square.h"

class Xwindow;

class UprightSquare: public Square{

  public:
    UprightSquare(int r, int c, std::string color);
    int remove(int count = 0);
    void draw(Xwindow *window, int x, int y);

};


#endif
