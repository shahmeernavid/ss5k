#ifndef __PATTERN_H__
#define __PATTERN_H__

#include <vector>
#include <utility>
#include <string>

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
    virtual std::vector<Square*> check(int r, int c, const Grid& g) = 0;
    // given left top most square, gives position of new square
    virtual std::pair<int, int> newPos(int r, int c) = 0;
    // gives type of new square
    virtual std::string newType() = 0;
    int getPriority();

    virtual Pattern* copy() = 0;
};


#endif
