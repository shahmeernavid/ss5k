#ifndef __BASIC_PATTERN_H__
#define __BASIC_PATTERN_H__

#include "pattern.h"

class BasicPattern: public Pattern{

  public:
    BasicPattern(int p = 0);
    std::pair<std::vector<Square*>, std::pair<std::string, std::pair<int, int> > > check(int r, int c, Grid& g);

    Pattern* copy();
};


#endif