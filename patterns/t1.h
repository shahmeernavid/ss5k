#ifndef __T_1_PATTERN_H__
#define __T_1_PATTERN_H__

#include "pattern.h"

class T1Pattern: public Pattern{

  public:
    T1Pattern(int p = 0);
    std::vector<Square*> check(int r, int c, const Grid& g);
    std::pair<int, int> newPos(int r, int c);
    std::string newType();


    Pattern* copy();
};


#endif