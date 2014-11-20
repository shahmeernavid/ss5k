#ifndef __BASIC_PATTERN_H__
#define __BASIC_PATTERN_H__

#include "pattern.h"

class BasicPattern: public Pattern{

  public:
    BasicPattern(int p = 0);
    std::vector<Square*> check(int r, int c, Grid& g) const;
};


#endif