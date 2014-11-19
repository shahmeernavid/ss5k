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
  // neighbouring cells
  std::map<int, Square*> neighbours;
  // cell's type
  std::string type;
  // cell's color
  std::string color;

  public:
    // constructors
    Square(int r, int c, const std::string& type, const std::string& color, Grid* g);
    //destructor
    virtual ~Square();
    // getter for color
    std::string getColor();
    virtual int remove();
    virtual int remove(std::string c);
    friend std::ostream& operator<<(std::ostream& out, Square& square);

};


#endif