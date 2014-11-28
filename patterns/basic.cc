#include <iostream>
#include <string>
#include "basic.h"
#include "../grid.h"

using namespace std;

BasicPattern::BasicPattern(int p):Pattern(p){}

vector<Square*> BasicPattern::check(int r, int c, const Grid& g) {
  Square* start = g.getSquare(r, c);
  vector<Square*> output;
  if(!start){
    return output;
  }

  string color = start->getColor();
  // down
  if(g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
  }
  // right
  else if(g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
  }
  // left
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c-2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c-2, color));
  }
  // top
  else if(g.getSquare(r-1, c, color) && g.getSquare(r-2, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r-2, c, color));
  }
  // middle vertical
  else if(g.getSquare(r-1, c, color) && g.getSquare(r+1, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r+1, c, color));
  }
  // middle horizontal
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c+1, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c+1, color));
  }
  return output;
}


pair<int, int> BasicPattern::newPos(int r, int c){
  return make_pair(-1, -1);
}

string BasicPattern::newType(){
  return "";
}

Pattern* BasicPattern::copy(){
  BasicPattern* copy = new BasicPattern(priority);
  return copy;
}