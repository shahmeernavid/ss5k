#include <iostream>
#include <string>
#include "l4.h"
#include "../grid.h"

using namespace std;

/*
  xxx
    x
    x

*/

L4Pattern::L4Pattern(int p):Pattern(p){}

vector<Square*> L4Pattern::check(int r, int c, Grid& g) {
  Square* start = g.getSquare(r, c);
  vector<Square*> output;
  
  if(!start){
    return output;
  }

  string color = start->getColor();
  /*
    oxx
      x
      x
  */
  if(g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color) && g.getSquare(r+1, c+2, color) && g.getSquare(r+2, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
    output.push_back(g.getSquare(r+1, c+2, color));
    output.push_back(g.getSquare(r+2, c+2, color));
  }
  /*
    xox
      x
      x
  */
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c+1, color) && g.getSquare(r+1, c+1, color) && g.getSquare(r+2, c+1, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r+1, c+1, color));
    output.push_back(g.getSquare(r+2, c+1, color));
  }
  /*
    xxo
      x
      x
  */
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c-2, color) && g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c-2, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
  }
  /*
    xxx
      o
      x
  */
  else if(g.getSquare(r+1, c, color) && g.getSquare(r-1, c, color) && g.getSquare(r-1, c-1, color) && g.getSquare(r-1, c-2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r-1, c-1, color));
    output.push_back(g.getSquare(r-1, c-2, color));
  }
  /*
    xxx
      x
      o
  */
  else if(g.getSquare(r-1, c, color) && g.getSquare(r-2, c, color) && g.getSquare(r-2, c-1, color) && g.getSquare(r-2, c-2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r-2, c, color));
    output.push_back(g.getSquare(r-2, c-1, color));
    output.push_back(g.getSquare(r-2, c-2, color));
  }
  
  return output;
}


// input expected to ne left-top most element
pair<int, int> L4Pattern::newPos(int r, int c){
  return make_pair(r, c+2);
}

string L4Pattern::newType(){
  return "unstable";
}

Pattern* L4Pattern::copy(){
  L4Pattern* copy = new L4Pattern(priority);
  return copy;
}