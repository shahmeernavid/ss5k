#ifndef __L_4_PATTERN_H__
#define __L_4_PATTERN_H__

#include "pattern.h"

class L4Pattern: public Pattern{

  public:
    L4Pattern(int p = 0);
    std::vector<Square*> check(int r, int c, Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif