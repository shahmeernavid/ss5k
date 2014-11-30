#include "root.h"
#include "../grid.h"
#include "../display/window.h"
#include "../settings.h"

using namespace std;

RootSquare::RootSquare(int r, int c, string color):Square(r, c, color, "root"){}

void RootSquare::remove(int count){
  return grid->remove(r, c);
}


void RootSquare::draw(Xwindow *window, int x, int y) {

    int height = Settings::SQUARE_HEIGHT; // save us some typing
    int width = Settings::SQUARE_WIDTH;

    int ribbon_height = height / 5;
    int ribbon_width = width / 5;

    window->fillRectangle(x, y, width, height, getColorInt());
    // vertical/horizontal stripes
    window->fillRectangle(x + 2 * ribbon_width, y, ribbon_width, height, 0);
    window->fillRectangle(x, y + 2 * ribbon_height, width, ribbon_height, 0);

    window->fillRectangle(x + 2 * ribbon_width, y + 2 * ribbon_width,
        ribbon_width, ribbon_height, 1);

    window->drawString(x + (width / 2) - 3, y + (height / 2) + 4, "R", 0); 
}
