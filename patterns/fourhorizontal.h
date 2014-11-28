#ifndef __FOUR_HORIZONTAL_PATTERN_H__
#define __FOUR_HORIZONTAL_PATTERN_H__

#include "pattern.h"

class FourHorizontalPattern: public Pattern{

  public:
    FourHorizontalPattern(int p = 0);
    std::vector<Square*> check(int r, int c, Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif