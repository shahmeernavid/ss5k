#include "basic.h"
#include "../grid.h"
#include "../display/window.h"
#include "../settings.h"

using namespace std;

BasicSquare::BasicSquare(int r, int c, string color):Square(r, c, color, "basic"){}

void BasicSquare::remove(int count){
  return grid->remove(r, c);
}


void BasicSquare::draw(Xwindow *window, int x, int y) {
   
   window->fillRectangle(x, y, Settings::SQUARE_HEIGHT, Settings::SQUARE_WIDTH,
    getColorInt()); 
}
