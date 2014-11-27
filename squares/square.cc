#include <ostream>
#include "square.h"
#include "../grid.h"
#include "../settings.h"

using namespace std;


// Square* Square::create(int r, int c, string color, string type, Grid* g){
//   // if(type == "lateral"){
//   //   return new LateralSquare(r, c, color, g);
//   // }
//   // else if(type == "upright"){
//   //   return new UprightSquare(r, c, color, g);
//   // }
//   // else if(type == "unstable"){
//   //   return new UnstableSquare(r, c, color, g);
//   // }
//   // else if(type == "psychedelic"){
//   //   return new PsychedelicSquare(r, c, color, g);
//   // }
//   if(type == "basic"){
//     return new Square(r, c, color, g);
//   }
//   return NULL;
// }

Square::Square(int r, int c, string color, string t)
  :r(r), c(c), color(color), type(t){}

Square::~Square(){}

int Square::getRow(){
  return r;
}
int Square::getCol(){
  return c;
}

void Square::setRow(int row){
  r = row;
}
void Square::setCol(int col){
  c = col;
}

void Square::setGrid(Grid* g){
  grid = g;
}

int Square::remove(int count){
  return grid->remove(r, c);
}


string Square::getColor(){
  return color;
}

ostream& operator<<(ostream& out, Square& square){
  Settings const * settings = Settings::getInstance();
  // cerr << endl << "type: " << square.type << endl;
  out << settings->getTypeEncoding(square.type);
  // cerr << endl << "color: " << square.color << endl;
  // cerr << square.r << " " << square.c << endl;
  out << settings->getColorEncoding(square.color);
  
  return out;
}
