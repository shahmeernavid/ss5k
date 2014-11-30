#ifndef __T_4_PATTERN_H__
#define __T_4_PATTERN_H__

#include "pattern.h"

class T4Pattern: public Pattern{

  public:
    T4Pattern(int p = 0);
    std::vector<Square*> check(int r, int c, const Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif