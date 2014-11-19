#ifndef __GRID_H__ 
#define __GRID_H__

#include <vector>
#include "squares/square.h"
#include "patterns/pattern.h"
#include "levels/level.h"

class Grid{
  std::vector<std::vector<Square*> > board;
  std::vector<Pattern*> patterns;
  Level* level;
  static Grid* instance;

  Grid(int n, int m, Level* l);
  int processSwap();
  static void clean();
  ~Grid();

  public:
    static Grid* getInstance(int n, int m, Level* l);
    int swap(int r, int c, int z);
    void remove(int r, int c);
    void removeRow(int r);
    void removeCol(int c);
    Square* getSquare(int r, int c);
    Square* getSquare(int r, int c, std::string color);
    friend std::ostream& operator<<(std::ostream& out, Grid& grid);

};

#endif