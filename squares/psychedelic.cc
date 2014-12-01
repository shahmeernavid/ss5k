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


    window->fillRectangle(x, y, width, height, getColorInt());

    // top + bottom side
    for (int i = 0; i < 5; ++i) {
        window->fillRectangle(x + (i * ribbon_width), y, ribbon_width, ribbon_height, rand() % 10); 
        window->fillRectangle(x + (i * ribbon_width), y + height - ribbon_height, ribbon_width, ribbon_height, rand() % 10); 
    }
    // left + right
    for (int i = 0; i < 5; ++i) {
        window->fillRectangle(x, y + (i * ribbon_height), ribbon_width, ribbon_height, rand() % 10); 
        window->fillRectangle(x + width - ribbon_width, y + (i * ribbon_height), ribbon_width, ribbon_height, rand() % 10); 
    }

    

    window->drawString(x + (width / 2) - 3, y + (height / 2) + 3, "P", 1); 
}
