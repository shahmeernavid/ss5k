#ifndef __BASIC_PATTERN_H__
#define __BASIC_PATTERN_H__

#include "pattern.h"

class BasicPattern: public Pattern{

  public:
    BasicPattern(int p = 0);
    std::vector<Square*> check(int r, int c, const Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif