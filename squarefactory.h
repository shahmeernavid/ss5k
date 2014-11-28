#ifndef __SQUARE_FACTORY_H_
#define __SQUARE_FACTORY_H_

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <ostream>
#include <cstdlib>
#include "settings.h"


class Square;

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


  std::string getColor(int r, int c, int level);
  std::string getType(int r, int c, int level);
  void insert(std::vector<std::pair<std::string, double> >& array, std::pair<std::string, double> elem);
  std::string pick(std::map<std::string, double> mapping);

  public:
    static SquareFactory* getInstance();
    static void clean();

    // generate a square based on level/cords, etc
    Square* generateSquare(int r, int c, int level, std::string type, bool count);
    Square* generateIndependantSquare(int r, int c, int level, Grid& g, std::string type, bool count);
    // specifically create this square
    Square* createSquare(int r, int c, std::string color, std::string type, bool count);
    void reset();

    void setSequence(std::string seq);
    
};

#endif
