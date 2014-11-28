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
    Grid(int n, int m, int l = 0);
    Grid(std::istream& in, int rows, int l = 0); 
    ~Grid();
    int purgeMarked();
    bool isLocked(int r, int c);
    bool match(int r, int c, std::string color);
    int match(int r, int c);
    bool swap(int r, int c, int z);
    int hint();
    void scramble();
    int getLevel();
    std::vector<int> process();
    void remove(int r, int c);
    void removeRow(int r);
    void removeCol(int c);
    void removeColor(std::string color);
    void removeRect(int tr, int tc, int w, int h);
    Square* getSquare(int r, int c) const;
    Square* getSquare(int r, int c, std::string color) const;
    void levelChanged(int l);
    void drawSquares(Xwindow *window);
    friend std::ostream& operator<<(std::ostream& out, Grid& grid);

};

#endif
