#ifndef __L_2_PATTERN_H__
#define __L_2_PATTERN_H__

#include "pattern.h"

class L2Pattern: public Pattern{

  public:
    L2Pattern(int p = 0);
    std::vector<Square*> check(int r, int c, const Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif