#ifndef __LEVEL_H_
#define __LEVEL_H_

#include <vector>

class Level{
  std::vector<std::string> colors {"Red", "White", "Green", "Blue"};
  std::vector<std::string> squareTypes {"Basic", "Lateral", "Upright", "Psychedelic"};


  public:
    Level();
    virtual ~Level();
    virtual Square* getSquare() = 0;
    
};

#endif