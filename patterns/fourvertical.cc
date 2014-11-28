#include <iostream>
#include <string>
#include "fourvertical.h"
#include "../grid.h"

using namespace std;

FourVerticalPattern::FourVerticalPattern(int p):Pattern(p){}

vector<Square*> FourVerticalPattern::check(int r, int c, Grid& g) {
  Square* start = g.getSquare(r, c);
  vector<Square*> output;
  
  if(!start){
    return output;
  }

  string color = start->getColor();
  // leftmost
  if(g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color) && g.getSquare(r, c+3, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
    output.push_back(g.getSquare(r, c+3, color));
  }
  //rightmost
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c-2, color) && g.getSquare(r, c-3, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c-2, color));
    output.push_back(g.getSquare(r, c-3, color));
  }
  // middle horizontal
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
  }
  // middle horizontal
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c+1, color) && g.getSquare(r, c-2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c-2, color));
  }
  return output;
}


// input expected to ne left-top most element
pair<int, int> FourVerticalPattern::newPos(int r, int c){
  return make_pair(r, c+1);
}

string FourVerticalPattern::newType(){
  return "upright";
}

Pattern* FourVerticalPattern::copy(){
  FourVerticalPattern* copy = new FourVerticalPattern(priority);
  return copy;
}