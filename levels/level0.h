#ifndef __LEVEL_0_H_
#define __LEVEL_0_H_

#include <string>
#include <map>
#include "level.h"

class Level0: public Level{
  public:
    std::map<std::string, std::string> generateSquare();
    
};

#endif