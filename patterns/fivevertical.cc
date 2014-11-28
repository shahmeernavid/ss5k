#include <iostream>
#include <string>
#include "fivevertical.h"
#include "../grid.h"

using namespace std;

FiveVerticalPattern::FiveVerticalPattern(int p):Pattern(p){}

vector<Square*> FiveVerticalPattern::check(int r, int c, Grid& g) {
  Square* start = g.getSquare(r, c);
  vector<Square*> output;
  
  if(!start){
    return output;
  }

  string color = start->getColor();
  // leftmost
  if(g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color) && g.getSquare(r+3, c, color) && g.getSquare(r+4, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
    output.push_back(g.getSquare(r+3, c, color));
    output.push_back(g.getSquare(r+4, c, color));
  }
  //rightmost
  else if(g.getSquare(r-1, c, color) && g.getSquare(r-2, c, color) && g.getSquare(r-3, c, color) && g.getSquare(r-4, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r-2, c, color));
    output.push_back(g.getSquare(r-3, c, color));
    output.push_back(g.getSquare(r-4, c, color));
  }
  // middle left
  else if(g.getSquare(r-1, c, color) && g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color) && g.getSquare(r+3, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
    output.push_back(g.getSquare(r+3, c, color));
  }
  // middle right
  else if(g.getSquare(r-1, c, color) && g.getSquare(r+1, c, color) && g.getSquare(r-2, c, color) && g.getSquare(r-3, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r-2, c, color));
    output.push_back(g.getSquare(r-3, c, color));
  }
  // middle middle
  else if(g.getSquare(r-1, c, color) && g.getSquare(r+1, c, color) && g.getSquare(r-2, c, color) && g.getSquare(r+2, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r-2, c, color));
    output.push_back(g.getSquare(r+2, c, color));
  }
  return output;
}


// input expected to ne left-top most element
pair<int, int> FiveVerticalPattern::newPos(int r, int c){
  return make_pair(r+2, c);
}

string FiveVerticalPattern::newType(){
  return "psychedelic";
}

Pattern* FiveVerticalPattern::copy(){
  FiveVerticalPattern* copy = new FiveVerticalPattern(priority);
  return copy;
}