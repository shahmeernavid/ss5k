#ifndef __LEVEL_H_
#define __LEVEL_H_

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "../patterns/pattern.h"

class Level{
  std::vector<std::string> colors;
  std::vector<std::string> squareTypes;
  std::vector<Pattern*> patterns;
  Grid* grid;
  vector<vector<int>> probabilities;


  public:
    Level();
    virtual ~Level();
    void init(int n, int m);
    std::vector<Pattern*>& getPatterns();
    void registerPattern(Pattern* p);
    virtual std::map<std::string, std::string> generateSquare() = 0;
    int swap(int r, int c, int z);
    void print(std::ostream& out);
    
};

#endif