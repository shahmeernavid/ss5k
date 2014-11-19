#ifndef __PATTERN_H__
#define __PATTERN_H__


// forward declarations
class Grid;
class Square;

class Pattern{

  int priority;

  public:
    Pattern(int p);
    virtual ~Pattern();
    virtual bool check(int r, int c, Grid& g) = 0;
    int getPriority();
};


#endif