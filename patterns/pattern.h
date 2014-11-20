#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <vector>

// forward declarations
class Grid;
class Square;

class Pattern{

  int priority;

  public:
    Pattern(int p);
    virtual ~Pattern();
    // returns squares to be removed
    virtual std::vector<Square*> check(int r, int c, Grid& g) const = 0;
    int getPriority();
};


#endif