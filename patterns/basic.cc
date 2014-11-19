#include <string>
#include "basic.h"
#include "../grid.h"

using namespace std;

BasicPattern::BasicPattern(int p):Pattern(p){}

bool BasicPattern::check(int r, int c, Grid& g){
  Square* start = g.getSquare(r, c);
  if(!start){
    return false;
  }
  string color = start->getColor();
  int count = 1;

  if(g.getSquare(r+1, c, color)){
    count += (g.getSquare(r+2, c, color)) ? 2 : 1;
  }
  if(g.getSquare(r-1, c, color)){
    count += (g.getSquare(r-2, c, color)) ? 2 : 1;
  }
  if(g.getSquare(r, c+1, color)){
    count += (g.getSquare(r, c+2, color)) ? 2 : 1;
  }
  if(g.getSquare(r, c-1, color)){
    count += (g.getSquare(r, c-2, color)) ? 2 : 1;
  }

  return count >= 3;
}