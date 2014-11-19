#include <iostream>
#include "grid.h"
#include "levels/level.h"
#include "levels/level0.h"
#include "squares/square.h"
#include "patterns/pattern.h"
#include "patterns/basic.h"

using namespace std;

int main(int cargs, char*[] args){
  // create a new level
  Level* l = new Level0();
  l->init(10, 10);
  l->init(stream);

  // give the level the basic pattern
  Pattern* p = new BasicPattern(0);
  l->registerPattern(p);

  l->print(cout);

  l->swap(0, 0, 1);

  l->print(cout);

  delete l;
  delete p;
}
