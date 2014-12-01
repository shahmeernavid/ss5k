#ifndef __GAME_H_
#define __GAME_H_

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "patterns/pattern.h"
#include "settings.h"
#include "display/game_display.h"

class Grid;
class Square;

class Game{
  Grid* grid;
  int level;
  Settings const * settings;
  GameDisplay* display;
  ScoreBoard* scoreboard;

  // singleton pattern stuff
  static Game* instance;


  public:
    static Game* getInstance();
    static void clean();
    Game();
    ~Game();

    // gameplay interactions
    void init(std::istream& in, int rows);
    void init(int n, int m);
    void init();
    int oppositeDirection(int z);
    void swap(int r, int c, int z, bool d = false);
    int incrementLevel();
    int decrementLevel();
    int setLevel(int l, bool init = false);
    void hint();
    void scramble();
    void reset(bool print = true);
    void start();

    int getLevel();
    int movesLeft();
    void drawSquares(Xwindow* window);
    ScoreBoard* getScoreBoard();

    void setUpDisplay(std::ostream& out, bool window);

    // temporary (maybe)
    void print(std::ostream& out);
    
};

#endif
