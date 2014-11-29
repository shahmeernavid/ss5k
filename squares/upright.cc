#include "upright.h"
#include "../grid.h"
#include "../display/window.h"

using namespace std;

UprightSquare::UprightSquare(int r, int c, string color):Square(r, c, color, "upright"){}

void UprightSquare::remove(int count){
 return grid->removeCol(c);
}

void UprightSquare::draw(Xwindow *window, int x, int y) {
   
   int height = Settings::SQUARE_HEIGHT; // save some typing
   int width = Settings::SQUARE_WIDTH;
   int narrow_width = Settings::SQUARE_WIDTH / 5;

   window->fillRectangle(x, y, narrow_width, height, 8); 
   window->fillRectangle(x + narrow_width, y, narrow_width * 3, height, getColorInt()); 
   window->fillRectangle(x + 4 * narrow_width, y, narrow_width, height, 8); 

   window->drawString(x + (width / 2) - 5, y + (height / 2) + 5, "US", 9);
}
