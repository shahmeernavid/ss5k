#include "psychedelic.h"
#include "../grid.h"
#include "../display/window.h"

using namespace std;

PsychedelicSquare::PsychedelicSquare(int r, int c, string color):Square(r, c, color, "psychedelic"){}

int PsychedelicSquare::remove(int count){
  if(count == 4){
    return grid->removeRect(r, c, 5, 5);
  }
  return grid->removeRect(r, c, 3, 3);
  
}

void PsychedelicSquare::draw(Xwindow *window, int x, int y) {
   
   window->fillRectangle(x, y, 50, 50, 1); 
}
