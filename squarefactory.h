#ifndef __SQUARE_FACTORY_H_
#define __SQUARE_FACTORY_H_

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "squares/square.h"
#include "squares/basic.h"
#include "settings.h"


class SquareFactory{
  static SquareFactory* instance;

  // const pointer - cant modify settings
  Settings const * settings;

  std::vector<std::string> colorSequence;
  // for color sequence
  int index;
  int productionCount;

  SquareFactory();
  ~SquareFactory();

  public:
    static SquareFactory* getInstance();
    static void clean();

    // generate a square based on level/cords, etc
    Square* generateSquare(int r, int c, int level, Grid* g);
    // specifically create this square
    Square* createSquare(int r, int c, std::string color, std::string type);
    void reset();

    void setSequence(std::string seq);
    
};

#endif