#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <vector>
#include <utility>

// forward declarations
class Grid;
class Square;

class Pattern{
  protected:
    int priority;

  public:
    Pattern(int p);
    virtual ~Pattern();
    // returns squares to be removed + square to be generated
    virtual std::pair<std::vector<Square*>, std::pair<std::string, std::pair<int, int> > > check(int r, int c, Grid& g) = 0;
    int getPriority();

    virtual Pattern* copy() = 0;
};


#endif