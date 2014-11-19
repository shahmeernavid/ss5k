#ifndef __LEVEL_0_H_
#define __LEVEL_0_H_

#include "level.h"

class Level0: public Level{
  public:
    Level0();
    std::map<std::string, std::string> generateSquare();
    
};

#endif