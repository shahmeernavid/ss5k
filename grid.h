#ifndef __GRID_H__ 
#define __GRID_H__

#include <vector>
#include <istream>
#include "squares/square.h"
#include "squarefactory.h"
#include "settings.h"

class Grid{
  std::vector<std::vector<Square*> > board;
  std::map<int, bool> locked;
  int level;
  Settings const * settings;
  SquareFactory* factory;

  void collapse();
  void fill();

  public:
    Grid(int n, int m);
    Grid(std::istream& in, int rows); 
    ~Grid();
    int purgeMarked();
    bool isLocked(int r, int c);
    bool match(int r, int c, std::string color);
    bool swap(int r, int c, int z);
    std::vector<int> process();
    void remove(int r, int c);
    void removeRow(int r);
    void removeCol(int c);
    void removeColor(std::string color);
    void removeRect(int tr, int tc, int w, int h);
    Square* getSquare(int r, int c);
    Square* getSquare(int r, int c, std::string color);
    void levelChanged(int l);
    void drawSquares(Xwindow *window);
    friend std::ostream& operator<<(std::ostream& out, Grid& grid);

};

#endif
