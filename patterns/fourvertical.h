#ifndef __FOUR_VERTICAL_PATTERN_H__
#define __FOUR_VERTICAL_PATTERN_H__

#include "pattern.h"

class FourVerticalPattern: public Pattern{

  public:
    FourVerticalPattern(int p = 0);
    std::vector<Square*> check(int r, int c, Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif