#ifndef __SQUARE_FACTORY_H_
#define __SQUARE_FACTORY_H_

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include "squares/square.h"
#include "squares/basic.h"


class SquareFactory{
  // outermost index represents level
  // contains a map of each color/type -> porbability of that type occuring
  // so to get probability of red psychadelic square on level 3: probs[2]["psychadelic"]
  // restriction: colors and types cant have same name, ie: dont be an idiot
  std::vector<std::map<std::string, double> > probs;

  string getColor(int r, int c, int level, Grid* g);
  string getType(int r, int c, int level, Grid* g);

  public:
    SquareFactory();
    // generate a square based on level/cords, etc
    Square* generateSquare(int r, int c, int level, Grid* g);
    // specifically create this square
    Square* createSquare(int r, int c, std::string color, std::string type);
    
};

#endif