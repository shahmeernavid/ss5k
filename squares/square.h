#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <vector>
#include <string>
#include <map>
#include <iostream>

// forward decaration
class Grid;

class Square{
  // row and column coords of this cell
  int r, c;
  // the grid this cell is on
  Grid* grid;
  // cell's color
  std::string color;
  std::string type;
  // marker for if this square has been removed
  bool removed;

  public:
    // constructors
    Square(int r, int c, std::string color, std::string t);
    //destructor
    virtual ~Square();
    // getter for color
    std::string getColor();
    void setGrid(Grid* g);
    virtual int remove();
    virtual int remove(std::string c);
    // static Square* create(int r, int c, std::string color, std::string type, Grid* g);
    friend std::ostream& operator<<(std::ostream& out, Square& square);

};


#endif