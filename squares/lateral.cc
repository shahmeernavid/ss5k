#include "lateral.h"
#include "../grid.h"
#include "../display/window.h"

using namespace std;

LateralSquare::LateralSquare(int r, int c, string color):Square(r, c, color, "lateral"){}

int LateralSquare::remove(int count){
  return grid->removeRow(r);
}

void LateralSquare::draw(Xwindow *window, int x, int y) {
   
   window->fillRectangle(x, y, 50, 50, 1); 
}
