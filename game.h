#ifndef __LEVEL_H_
#define __LEVEL_H_

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "../patterns/pattern.h"

class Game{
  std::vector<std::string> colors;
  std::vector<std::string> squareTypes;
  std::vector<Pattern*> patterns;
  Grid* grid;
  int level;
  // outermost index represents level
  // contains a map of each color/type -> porbability of that type occuring
  // so to get probability of red psychadelic square on level 3: probs[2]["psychadelic"]
  // restriction: colors and types cant have same name, ie: dont be an idiot
  std::vector<std::map<std::string, int> > probs;

  void registerPattern(Pattern* p);

  // singleton pattern stuff
  Game();
  static Game* instance;


  public:
    static Grid& getInstance();
    ~Game();
    std::vector<Pattern*>& getPatterns();
    void registerPattern(Pattern* p);
    std::map<std::string, std::string> generateSquare();

    // gameplay interactions
    void init(int n, int m);
    int swap(int r, int c, int z);
    int incrementLevel();
    int decrementLevel();

    // temporary (maybe)
    void print(std::ostream& out);
    
};

#endif