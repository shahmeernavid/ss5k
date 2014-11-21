#include <iostream>
#include "grid.h"
#include "game.h"
#include "squares/square.h"

using namespace std;

int main(int argc, char* args[]){
  Game* g = Game::getInstance();
  g->init(10, 10);
  g->print(cout);
  g->swap(0, 0, 1);
  g->print(cout);

  // delete g;
}
