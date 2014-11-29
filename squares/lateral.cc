#include "lateral.h"
#include "../grid.h"
#include "../display/window.h"

using namespace std;

LateralSquare::LateralSquare(int r, int c, string color):Square(r, c, color, "lateral"){}

void LateralSquare::remove(int count){
  return grid->removeRow(r);
}

void LateralSquare::draw(Xwindow *window, int x, int y) {
   
   int width = Settings::SQUARE_WIDTH; // save some typing
   int height = Settings::SQUARE_HEIGHT; 
   int narrow_height = Settings::SQUARE_HEIGHT / 5;

   window->fillRectangle(x, y, width, narrow_height, 8); 
   window->fillRectangle(x, y + narrow_height, width, narrow_height * 3, getColorInt()); 
   window->fillRectangle(x, y + narrow_height * 4, width, narrow_height, 8); 

   window->drawString(x + (width / 2) - 5, y + (height / 2) + 5, "LS", 9);
}
