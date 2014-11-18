#ifndef __GRID_H__ 
#define __GRID_H__

#include <vector>
#include "square.h"

class Grid{
  std::vector<std::vector<Square*> > board;
  static Grid* instance;

  void processMatches();
  Grid(int n, int m);
  ~Grid();
  static void clean();

  public:
    static Grid& getInstance();
    int move(int r, int c, int z);

};

#endif