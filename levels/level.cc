#include "level.h"
using namespace std;

Level::Level(){}

Level::~Level(){}

// ensures patterns are in correct order
void Level::registerPattern(Pattern* p){
  for(int i = 0; i < patterns.size(); i++){
    if(patterns[i]->getPriority() > p->getPriority()){
      patterns.insert(patterns.begin()+i, p);
      return;
    }
  }
  // if we dont insert, then just push
  patterns.push_back(p);
}

vector<Pattern*>& Level::getPatterns(){
  return patterns;
}

