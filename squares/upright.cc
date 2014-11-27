#include "upright.h"
#include "../grid.h"
#include "../display/window.h"

using namespace std;

UprightSquare::UprightSquare(int r, int c, string color):Square(r, c, color, "upright"){}

int UprightSquare::remove(int count){
 return grid->removeCol(c);
}

void UprightSquare::draw(Xwindow *window, int x, int y) {
   
   window->fillRectangle(x, y, 50, 50, 1); 
}
