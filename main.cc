#include <iostream>
#include "grid.h"
#include "levels/level.h"
#include "levels/level0.h"
#include "squares/square.h"
#include "patterns/pattern.h"
#include "patterns/basic.h"

using namespace std;

int main(){
  Level* l = new Level0();
  Pattern* p = new BasicPattern(0);
  l->registerPattern(p);
  Grid* g = Grid::getInstance(10, 10, l);

  cout << *g;

  delete l;
  delete p;
}
