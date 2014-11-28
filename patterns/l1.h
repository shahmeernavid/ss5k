#ifndef __L_1_PATTERN_H__
#define __L_1_PATTERN_H__

#include "pattern.h"

class L1Pattern: public Pattern{

  public:
    L1Pattern(int p = 0);
    std::vector<Square*> check(int r, int c, Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif