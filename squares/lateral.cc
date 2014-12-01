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
    int ribbon_height = height / 5;

    window->fillRectangle(x, y, width, height, getColorInt()); 

    window->fillRectangle(c*width, r*height, width, ribbon_height, 8);
    window->fillRectangle(c*width, r*height + height - ribbon_height, width, ribbon_height, 8);

    // window->fillRectangle(x, y, width, narrow_height, 8); 
    
    // window->fillRectangle(x, y + narrow_height * 4, width, narrow_height, 8); 

    window->drawString(x + (width / 2) - 3, y + (height / 2) + 3, "L", 1); 
}
