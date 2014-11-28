#include <iostream>
#include <string>
#include "fourhorizontal.h"
#include "../grid.h"

using namespace std;

FourHorizontalPattern::FourHorizontalPattern(int p):Pattern(p){}


vector<Square*> FourHorizontalPattern::check(int r, int c, const Grid& g) {
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


// input expected to ne leftmost element
pair<int, int> FourHorizontalPattern::newPos(int r, int c){
  return make_pair(r+1, c);
}

string FourHorizontalPattern::newType(){
  return "lateral";
}

Pattern* FourHorizontalPattern::copy(){
  FourHorizontalPattern* copy = new FourHorizontalPattern(priority);
  return copy;
}