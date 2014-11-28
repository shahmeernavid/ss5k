#include <iostream>
#include <string>
#include "l1.h"
#include "../grid.h"

using namespace std;

/*

xxx
x
x

*/

L1Pattern::L1Pattern(int p):Pattern(p){}

vector<Square*> L1Pattern::check(int r, int c, const Grid& g) {
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
  if(g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color) && g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
  }
  /*
    xox
    x
    x
  */
  else if(g.getSquare(r, c+1, color) && g.getSquare(r, c-1, color) && g.getSquare(r+1, c-1, color) && g.getSquare(r+2, c-1, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c+1, color)); 
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r+1, c-1, color));
    output.push_back(g.getSquare(r+2, c-1, color));
  }
  /*
    xxo
    x
    x
  */
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c-2, color) && g.getSquare(r+1, c-2, color) && g.getSquare(r+2, c-2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c-2, color));
    output.push_back(g.getSquare(r+1, c-2, color));
    output.push_back(g.getSquare(r+2, c-2, color));
  }
  /*
    xxx
    o
    x
  */
  else if(g.getSquare(r-1, c, color) && g.getSquare(r+1, c, color) && g.getSquare(r-1, c+1, color) && g.getSquare(r-1, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r-1, c+1, color));
    output.push_back(g.getSquare(r-1, c+2, color));
  }
  /*
    xxx
    x
    o
  */
  else if(g.getSquare(r-1, c, color) && g.getSquare(r-2, c, color) && g.getSquare(r-2, c+1, color) && g.getSquare(r-2, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r-2, c, color));
    output.push_back(g.getSquare(r-2, c+1, color));
    output.push_back(g.getSquare(r-2, c+2, color));
  }
  return output;
}


// input expected to ne left-top most element
pair<int, int> L1Pattern::newPos(int r, int c){
  return make_pair(r, c);
}

string L1Pattern::newType(){
  return "unstable";
}

Pattern* L1Pattern::copy(){
  L1Pattern* copy = new L1Pattern(priority);
  return copy;
}