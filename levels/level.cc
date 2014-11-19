#include <cmath>
#include "level.h"
#include "../grid.h"
using namespace std;

Level::Level():grid(NULL){}

Level::~Level(){
  delete grid;
}

void Level::init(istream& in){
  grid = new Grid(in, this);
}

void Level::init(int n, int m){
  grid = new Grid(n, m, this);
}

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

int Level::swap(int r, int c, int z){
  bool result = grid->swap(r, c, z);
  if(result){
    cerr << "process" << endl;
    vector<int> scores = grid->process();
    int output = 0;
    for(int i = 0; i < scores.size(); i++){
      output += pow(2, i+1)*scores[i];
    }
    return output;
  }
  return 0;
}

void Level::print(ostream& out){
  out << *grid;
}
