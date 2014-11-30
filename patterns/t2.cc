#include <iostream>
#include <string>
#include "t2.h"
#include "../grid.h"

using namespace std;

/*
  x
  xxx
  x
*/

T2Pattern::T2Pattern(int p):Pattern(p){}

vector<Square*> T2Pattern::check(int r, int c, const Grid& g) {
  Square* start = g.getSquare(r, c);
  vector<Square*> output;
  
  if(!start){
    return output;
  }

  string color = start->getColor();
  /*
    o
    xxx
    x
  */
  if(g.getSquare(r+1, c, color) && g.getSquare(r+2, c, color) && g.getSquare(r+1, c+1, color) && g.getSquare(r+1, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r+2, c, color));
    output.push_back(g.getSquare(r+1, c+1, color));
    output.push_back(g.getSquare(r+1, c+2, color));
  }
  /*
    x
    xxx
    o
  */
  else if(g.getSquare(r-1, c, color) && g.getSquare(r-2, c, color) && g.getSquare(r-1, c+1, color) && g.getSquare(r-1, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-2, c, color));
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r-1, c+1, color));
    output.push_back(g.getSquare(r-1, c+2, color));
  }
  /*
    x
    xox
    x
  */
  else if(g.getSquare(r-1, c-1, color) && g.getSquare(r+1, c-1, color) && g.getSquare(r, c-1, color) && g.getSquare(r, c+1, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r-1, c-1, color));
    output.push_back(g.getSquare(r+1, c-1, color));
  }
  /*
    x
    xxo
    x
  */
  else if(g.getSquare(r, c-1, color) && g.getSquare(r, c-2, color) && g.getSquare(r-1, c-2, color) && g.getSquare(r+1, c-2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r, c-1, color));
    output.push_back(g.getSquare(r, c-2, color));
    output.push_back(g.getSquare(r-1, c-2, color));
    output.push_back(g.getSquare(r+1, c-2, color));
  }
  /*
    x
    oxx
    x
  */
  else if(g.getSquare(r-1, c, color) && g.getSquare(r+1, c, color) && g.getSquare(r, c+1, color) && g.getSquare(r, c+2, color)){
    output.push_back(start);
    output.push_back(g.getSquare(r-1, c, color));
    output.push_back(g.getSquare(r+1, c, color));
    output.push_back(g.getSquare(r, c+1, color));
    output.push_back(g.getSquare(r, c+2, color));
  }
  
  return output;
}


// input expected to ne left-top most element
pair<int, int> T2Pattern::newPos(int r, int c){
  return make_pair(r+1, c+1);
}

string T2Pattern::newType(){
  return "unstable";
}

Pattern* T2Pattern::copy(){
  T2Pattern* copy = new T2Pattern(priority);
  return copy;
}