#ifndef __PSYCHEDELIC_SQUARE_H__
#define __PSYCHEDELIC_SQUARE_H__

#include "square.h"

class Xwindow;

class PsychedelicSquare: public Square{

  public:
    PsychedelicSquare(int r, int c, std::string color);
    int remove(int count = 0);
    void draw(Xwindow *window, int x, int y);

};


#endif
