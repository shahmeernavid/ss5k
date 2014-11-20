#include <ostream>
#include "square.h"
#include "../grid.h"

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

Square::Square(int r, int c, string color, Grid* g)
  :r(r), c(c), grid(g), color(color), removed(false){

    cerr << "created";
  }

Square::~Square(){}

int Square::remove(){
  if(!removed){
    removed = true;
    return grid->remove(r, c);
  }
  return 0;
}

int Square::remove(string c){
  if(color == c){
    return remove();
  }
  return 0;
}

string Square::getColor(){
  return color;
}

ostream& operator<<(ostream& out, Square& square){
  out << square.color;
  return out;
}