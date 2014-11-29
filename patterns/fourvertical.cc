#include <iostream>
#include <string>
#include "fourvertical.h"
#include "../grid.h"

using namespace std;

FourVerticalPattern::FourVerticalPattern(int p):Pattern(p){}

vector<Square*> FourVerticalPattern::check(int r, int c, const Grid& g) {
  Square* start = g.getSquare(r, c);
  vector<Square*> output;
  
  if(!start){
    return output;
  }

  string color = start->getColor();
  // leftmost
  if(g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color) && g.getSquare(r+3, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
    output.push_back(g.getSquare(r+3, c, color));
  }
  //rightmost
  else if(g.getSquare(r-1, c, color) && g.getSquare(r-2, c, color) && g.getSquare(r-3, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r-2, c, color));
    output.push_back(g.getSquare(r-3, c, color));
  }
  // middle horizontal
  else if(g.getSquare(r-1, c, color) && g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
  }
  // middle horizontal
  else if(g.getSquare(r-1, c, color) && g.getSquare(r+1, c, color) && g.getSquare(r-2, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r-2, c, color));
  }
  return output;
}


// input expected to ne left-top most element
pair<int, int> FourVerticalPattern::newPos(int r, int c){
  return make_pair(r+1, c);
}

string FourVerticalPattern::newType(){
  return "upright";
}

Pattern* FourVerticalPattern::copy(){
  FourVerticalPattern* copy = new FourVerticalPattern(priority);
  return copy;
}