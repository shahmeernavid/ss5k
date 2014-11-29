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
   
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            window->fillRectangle(x + (i * 10), y + (j * 10), 10, 10, rand() % 10); 
        }
    }

    window->fillRectangle(x + 10, y + 10, 30, 30, getColorInt());
    window->drawString(x + (width / 2) - 3, y + (height / 2) + 3, "P", 9); 
}
