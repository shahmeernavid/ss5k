#ifndef __GAME_H_
#define __GAME_H_

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "patterns/pattern.h"
#include "settings.h"

class Grid;
class Square;

class Game{
  Grid* grid;
  int level;
  Settings const * settings;

  // singleton pattern stuff
  static Game* instance;

  int setLevel(int l);

  public:
    static Game* getInstance();
    static void clean();
    Game();
    ~Game();


    // gameplay interactions
    void init(std::istream& in);
    void init(int n, int m);
    int swap(int r, int c, int z);
    int incrementLevel();
    int decrementLevel();
    void hint();
    void scramble();
    void reset();

    // temporary (maybe)
    void print(std::ostream& out);
    
};

#endif