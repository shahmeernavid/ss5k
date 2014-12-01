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
    int ribbon_width = Settings::SQUARE_WIDTH / 5;


    window->fillRectangle(x, y, width, height, getColorInt()); 

    window->fillRectangle(c*width, r*height, ribbon_width, height, 8);
    window->fillRectangle(c*width + width - ribbon_width, r*height, ribbon_width, height, 8);

    // window->fillRectangle(c*width, r*height, width, ribbon_height, 8);
    // window->fillRectangle(c*width, r*height + height - ribbon_height, width, ribbon_height, 8);



    window->drawString(x + (width / 2) - 3, y + (height / 2) + 3, "U", 1); 
}
