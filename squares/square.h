#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "../display/window.h"

// forward decaration
class Grid;

class Square{
  protected:
    // row and column coords of this cell
    int r, c;
    // the grid this cell is on
    Grid* grid;
    // cell's color
    std::string color;
    std::string type;

  public:
    // constructors
    Square(int r, int c, std::string color, std::string t);
    //destructor
    virtual ~Square();
    // getter for color
    std::string getColor();
    int getRow();
    int getCol();
    void setRow(int row);
    void setCol(int col);
    void setGrid(Grid* g);
    virtual int remove(int count = 0);
    virtual void draw(Xwindow *window, int x, int y) = 0;
    // static Square* create(int r, int c, std::string color, std::string type, Grid* g);
    friend std::ostream& operator<<(std::ostream& out, Square& square);

};


#endif
