#include "psychedelic.h"
#include "../grid.h"
#include "../display/window.h"

using namespace std;

PsychedelicSquare::PsychedelicSquare(int r, int c, string color):Square(r, c, color, "psychedelic"){}

void PsychedelicSquare::remove(int count){
  return grid->removeColor(color);
}

void PsychedelicSquare::draw(Xwindow *window, int x, int y) {
   
   window->fillRectangle(x, y, 50, 50, 1); 
}
