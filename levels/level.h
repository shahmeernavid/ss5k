#ifndef __LEVEL_H_
#define __LEVEL_H_

#include <vector>
#include <string>
#include <map>
#include "../patterns/pattern.h"

class Level{
  std::vector<std::string> colors;
  std::vector<std::string> squareTypes;
  std::vector<Pattern*> patterns;


  public:
    Level();
    virtual ~Level();
    std::vector<Pattern*>& getPatterns();
    void registerPattern(Pattern* p);
    virtual std::map<std::string, std::string> generateSquare() = 0;
    
};

#endif