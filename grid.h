#ifndef __GRID_H__ 
#define __GRID_H__

#include <vector>
#include "squares/square.h"
#include "levels/level.h"
#include "patterns/pattern.h"

class Grid{
  std::vector<std::vector<Square*> > board;
  Level* level;

  public:
    Grid(int n, int m, Level* l);
    ~Grid();
    bool swap(int r, int c, int z);
    std::vector<int> process();
    void remove(int r, int c);
    void removeRow(int r);
    void removeCol(int c);
    Square* getSquare(int r, int c);
    Square* getSquare(int r, int c, std::string color);
    friend std::ostream& operator<<(std::ostream& out, Grid& grid);

};

#endif