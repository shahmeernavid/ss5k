#include "unstable.h"
#include "../grid.h"
#include "../display/window.h"

using namespace std;

UnstableSquare::UnstableSquare(int r, int c, string color):Square(r, c, color, "unstable"){}

void UnstableSquare::remove(int count){
  if(count == 4){
    return grid->removeRect(r-2, c-2, 5, 5);
  }
  return grid->removeRect(r-1, c-1, 3, 3);
  
}

void UnstableSquare::draw(Xwindow *window, int x, int y) {
   
   window->fillRectangle(x, y, 50, 50, 1); 
}
