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
  int height = Settings::SQUARE_HEIGHT;
  int width = Settings::SQUARE_WIDTH;

  window->fillRectangle(x, y, width, height, getColorInt());

  window->drawString(x + (width / 2) - 3, y + (height / 2) + 3, "R", 1); 
}
