#include <iostream>
#include <string>
#include "basic.h"
#include "../grid.h"

using namespace std;

BasicPattern::BasicPattern(int p):Pattern(p){}

pair<vector<Square*>, pair<string, pair<int, int> > > BasicPattern::check(int r, int c, Grid& g) {
  Square* start = g.getSquare(r, c);
  vector<Square*> output;
  if(!start){
    return make_pair(output, make_pair("basic", make_pair(r, c)));
  }

  output.push_back(start);
  string color = start->getColor();
  // down
  if(g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color)){
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
  }
  // right
  else if(g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color)){
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
  }
  return make_pair(output, make_pair("basic", make_pair(r, c)));
}

Pattern* BasicPattern::copy(){
  BasicPattern* copy = new BasicPattern(priority);
  return copy;
}