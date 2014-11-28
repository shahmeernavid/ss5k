#include <iostream>
#include <string>
#include "fivehorizontal.h"
#include "../grid.h"

using namespace std;

FiveHorizontalPattern::FiveHorizontalPattern(int p):Pattern(p){}

vector<Square*> FiveHorizontalPattern::check(int r, int c, Grid& g) {
  Square* start = g.getSquare(r, c);
  vector<Square*> output;
  
  if(!start){
    return output;
  }

  string color = start->getColor();
  // leftmost
  if(g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color) && g.getSquare(r, c+3, color) && g.getSquare(r, c+4, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
    output.push_back(g.getSquare(r, c+3, color));
    output.push_back(g.getSquare(r, c+4, color));
  }
  //rightmost
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c-2, color) && g.getSquare(r, c-3, color) && g.getSquare(r, c-4, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c-2, color));
    output.push_back(g.getSquare(r, c-3, color));
    output.push_back(g.getSquare(r, c-4, color));
  }
  // middle left
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color) && g.getSquare(r, c+3, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
    output.push_back(g.getSquare(r, c+3, color));
  }
  // middle right
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c+1, color) && g.getSquare(r, c-2, color) && g.getSquare(r, c-3, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c-2, color));
    output.push_back(g.getSquare(r, c-3, color));
  }
  // middle middle
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c+1, color) && g.getSquare(r, c-2, color) && g.getSquare(r, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c-2, color));
    output.push_back(g.getSquare(r, c+2, color));
  }
  return output;
}


// input expected to ne left-top most element
pair<int, int> FiveHorizontalPattern::newPos(int r, int c){
  return make_pair(r, c+2);
}

string FiveHorizontalPattern::newType(){
  return "psychedelic";
}

Pattern* FiveHorizontalPattern::copy(){
  FiveHorizontalPattern* copy = new FiveHorizontalPattern(priority);
  return copy;
}