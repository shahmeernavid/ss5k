#include <ostream>
#include "square.h"
#include "../grid.h"

using namespace std;


Square* Square::create(int r, int c, string color, string type, Grid* g){
  if(type == "lateral"){
    return LateralSquare(r, c, color, g);
  }
  else if(type == "upright"){
    return UprightSquare(r, c, color, g);
  }
  else if(type == "unstable"){
    return UnstableSquare(r, c, color, g);
  }
  else if(type == "psychedelic"){
    return PsychedelicSquare(r, c, color, g);
  }
  else if(type == "basic"){
    return Square(r, c, color, g);
  }
  return NULL;
}

Square::Square(int r, int c, string color, Grid* g)
  :r(r), c(c), grid(g), color(color){}

Square::~Square(){}

string Square::getColor(){
  return color;
}

int Square::remove(){
  int output = 0;
  for(int n = 0; n < neighbours.size(); n++){
    output += neighbours[n]->remove(color);
  }
  grid->remove(r, c);
  return output+1;
}

int Square::remove(string c){
  if(color == c){
    return remove();
  }
  return 0;
}

ostream& operator<<(ostream& out, Square& square){
  out << square.color;
  return out;
}