#include "basic.h"
#include "../display/window.h"

using namespace std;

BasicSquare::BasicSquare(int r, int c, string color):Square(r, c, color, "basic"){}

void BasicSquare::draw(Xwindow *window, int x, int y) {
   
   window->fillRectangle(x, y, 50, 50, 1); 
}
