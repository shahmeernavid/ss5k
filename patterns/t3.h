#ifndef __T_3_PATTERN_H__
#define __T_3_PATTERN_H__

#include "pattern.h"

class T3Pattern: public Pattern{

  public:
    T3Pattern(int p = 0);
    std::vector<Square*> check(int r, int c, const Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif