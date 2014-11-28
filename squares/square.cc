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
  :r(r), c(c), color(color), type(t), removed(false){}

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

void Square::mark(){
  removed = true;
}

bool Square::isMarked(){
  return removed;
}

string Square::getColor(){
  return color;
}

// this returns the appropriate integer representation of the colour for the
// Xwindow class
int Square::getColorInt() {
    if (color == "white") {
        return 0; 
    } else if (color == "black") {
        return 1;
    } else if (color == "red") {
        return 2;
    } else if (color == "green") {
        return 3;
    } else if (color == "blue") {
        return 4;
    } else if (color == "cyan") {
        return 5;
    } else if (color == "yellow") {
        return 6;
    } else if (color == "magenta") {
        return 7;
    } else if (color == "orange") {
        return 8;
    } else if (color == "brown") {
        return 9;
    } else {
        // should never reach here; bad colour
        return -1;
    }
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

void Square::drawEmptySquare(Xwindow *window, int x, int y){
  window->fillRectangle(x, y, Settings::SQUARE_HEIGHT, Settings::SQUARE_WIDTH, 1); 
}
