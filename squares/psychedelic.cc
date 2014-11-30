#include "psychedelic.h"
#include "../grid.h"
#include "../display/window.h"

using namespace std;

PsychedelicSquare::PsychedelicSquare(int r, int c, string color):Square(r, c, color, "psychedelic"){}

void PsychedelicSquare::remove(int count){
  return grid->removeColor(color);
}

void PsychedelicSquare::draw(Xwindow *window, int x, int y) {

    int height = Settings::SQUARE_HEIGHT; // save us some typing
    int width = Settings::SQUARE_WIDTH;

    int ribbon_height = height / 5;
    int ribbon_width = width / 5;
   
    for (int i = 0; i < 5; ++i) {
        window->fillRectangle(x + (i * ribbon_width), y, ribbon_width, ribbon_height, rand() % 10); 
        window->fillRectangle(x + (i * ribbon_width), y + 4 * ribbon_height, ribbon_width, ribbon_height, rand() % 10); 
    }

    for (int i = 0; i < 5; ++i) {
        window->fillRectangle(x, y + (i * ribbon_height), ribbon_width, ribbon_height, rand() % 10); 
        window->fillRectangle(x + 4 * ribbon_height, y + (i * ribbon_height), ribbon_width, ribbon_height, rand() % 10); 
    }

    window->fillRectangle(x + ribbon_width, y + ribbon_height, 3 * ribbon_width,
        3 * ribbon_height, getColorInt());
    window->drawString(x + (width / 2) - 3, y + (height / 2) + 3, "P", 1); 
}
