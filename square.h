#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <vector>
#include <string>

class Square{
  // row and column coords
  int r, c;
  std::vector<int> neighbours;
  std::string type;
  std::string color;

  public:
    Square(int r, int c, const std::string& type, const std::string& color);
};


#endif