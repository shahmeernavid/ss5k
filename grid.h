#ifndef __GRID_H__ 
#define __GRID_H__

#include <vector>
#include <istream>
#include "squares/square.h"
#include "squarefactory.h"
#include "settings.h"

class Grid{
  std::vector<std::vector<Square*> > board;
  int numCols;
  int level;
  Settings const * settings;
  SquareFactory* factory;

  void collapse();
  void fill();

  public:
    Grid(int n, int m);
    Grid(std::istream& in); 
    ~Grid();
    bool match(int r, int c, std::string color);
    bool swap(int r, int c, int z);
    std::vector<int> process();
    int remove(int r, int c);
    int removeRow(int r);
    int removeCol(int c);
    int removeColor(std::string color);
    int removeRect(int tr, int tc, int w, int h);
    Square* getSquare(int r, int c);
    Square* getSquare(int r, int c, std::string color);
    void levelChanged(int l);
    friend std::ostream& operator<<(std::ostream& out, Grid& grid);

};

#endif