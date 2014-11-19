#include <ostream>
#include "square.h"
#include "../grid.h"

using namespace std;

Square::Square(int r, int c, const std::string& type, const std::string& color, Grid* g)
  :r(r), c(c), grid(g), type(type), color(color){}

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
  out << square.type;
  out << "-";
  out << square.color;
  return out;
}