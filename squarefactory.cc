#include <iostream>
#include "squarefactory.h"
#include "settings.h"

using namespace std;

SquareFactory* SquareFactory::instance = NULL;

SquareFactory::SquareFactory():settings(Settings::getInstance()),index(-1){}

SquareFactory::~SquareFactory(){}

SquareFactory* SquareFactory::getInstance(){
  if(!instance){
    instance = new SquareFactory();
    atexit(clean);
  }
  return instance;
}
void SquareFactory::clean(){
  delete instance;
}

Square* SquareFactory::generateSquare(int r, int c, int level, Grid* g){
  productionCount++;
  if(index == -1){
    // generate square using probabilities here
    return new BasicSquare(r, c, "red");
  }
  else{
    string c = colorSequence[(index++)%colorSequence.size()];
    return NULL;
  }
}

// specifically create this square
Square* SquareFactory::createSquare(int r, int c, string color, string type){
  productionCount++;
  if(type == "basic"){
    return new BasicSquare(r, c, color);
  }
  else{
    return NULL;
  }
}

void SquareFactory::reset(){
  productionCount = 0;
  index = 0;
  colorSequence = vector<string>();
}

void SquareFactory::setSequence(string seq){

}