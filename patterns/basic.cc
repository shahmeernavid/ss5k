#include <iostream>
#include <string>
#include "basic.h"
#include "../grid.h"

using namespace std;

BasicPattern::BasicPattern(int p):Pattern(p){}

vector<Square*> check(int r, int c, Grid& g) const{
  vector<Square*> output(1, g.getSquare(r, c));
  if(!start){
    return false;
  }
  string color = start->getColor();
  // down
  if(g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color)){
    output.push(g.getSquare(r+1, c, color));
    output.push(g.getSquare(r+2, c, color));
  }
  // right
  else if(g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color)){
    output.push(g.getSquare(r, c+1, color));
    output.push(g.getSquare(r, c+2, color));
  }
  return output;
}