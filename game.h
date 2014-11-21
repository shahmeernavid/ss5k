#ifndef __GAME_H_
#define __GAME_H_

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "patterns/pattern.h"

class Grid;
class Square;

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
  static Game* instance;


  public:
    static Game* getInstance();
    static void clean();
    Game();
    ~Game();
    std::vector<Pattern*>& getPatterns();
    Square* generateSquare(int r, int c);
    Square* createSquare(int r, int c, std::string color, std::string type);
    int calculateScore(int removeCount);


    // gameplay interactions
    void init(std::istream& in);
    void init(int n, int m);
    int swap(int r, int c, int z);
    int incrementLevel();
    int decrementLevel();

    // temporary (maybe)
    void print(std::ostream& out);
    
};

#endif