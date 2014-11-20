#include <cmath>
#include "game.h"
#include "../grid.h"
using namespace std;

Game::Game():grid(NULL),level(0){
  // register patterns here

}

Game::~Game(){
  delete grid;
  for(int i =0; i < patterns.size(); i++){
    delete patterns[i];
  }
}

void Game::init(istream& in){
  grid = new Grid(in, this);
}

void Game::init(int n, int m){
  grid = new Grid(n, m, this);
}

// ensures patterns are in correct order
void Game::registerPattern(Pattern* p){
  for(int i = 0; i < patterns.size(); i++){
    if(patterns[i]->getPriority() > p->getPriority()){
      patterns.insert(patterns.begin()+i, p);
      return;
    }
  }
  // if we dont insert, then just push
  patterns.push_back(p);
}

vector<Pattern*>& Game::getPatterns(){
  return patterns;
}


// gameplay interactions

int incrementLevel(){
  return level++;
}
int decrementLevel(){
  if(level > 0){
    return level--;  
  }
  return level;
}

int Game::swap(int r, int c, int z){
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

void Game::print(ostream& out){
  out << *grid;
}
