#ifndef __GRID_H__ 
#define __GRID_H__

#include <vector>
#include <istream>
#include "squares/square.h"
#include "game.h"
#include "patterns/pattern.h"

class Grid{
  std::vector<std::vector<Square*> > board;
  Game* game;
  int numCols;

  void collapse();

  public:
    Grid(int n, int m, Game* g);
    Grid(std::istream& in, Game* g); 
    ~Grid();
    bool swap(int r, int c, int z);
    std::vector<int> process();
    int remove(int r, int c);
    // int removeRow(int r);
    // int removeCol(int c);
    Square* getSquare(int r, int c);
    Square* getSquare(int r, int c, std::string color);
    friend std::ostream& operator<<(std::ostream& out, Grid& grid);

};

#endif