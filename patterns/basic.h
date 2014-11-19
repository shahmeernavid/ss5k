#ifndef __BASIC_PATTERN_H__
#define __BASIC_PATTERN_H__

#include "pattern.h"

class BasicPattern: public Pattern{
  
  public:
    BasicPattern(int p = 0);
    virtual bool check(int r, int c, Grid& g);
};


#endif