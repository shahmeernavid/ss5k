#ifndef __FIVE_HORIZONTAL_PATTERN_H__
#define __FIVE_HORIZONTAL_PATTERN_H__

#include "pattern.h"

class FiveHorizontalPattern: public Pattern{

  public:
    FiveHorizontalPattern(int p = 0);
    std::vector<Square*> check(int r, int c, Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif