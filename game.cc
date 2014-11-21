#include <cmath>
#include <cstdlib>
#include "game.h"
#include "grid.h"
#include "squares/basic.h"
#include "patterns/basic.h"
using namespace std;

Game* Game::instance = NULL;

void Game::clean(){
  delete instance;
}

Game* Game::getInstance(){
  if(!instance){
    instance = new Game();
    atexit(clean);
  }
  return instance;
}

Game::Game():grid(NULL),level(0){
  // register patterns here
  patterns.push_back(new BasicPattern(0));
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

// string getColor(int r, int c){
  
// }

// edit to intoduce randomness
Square* Game::generateSquare(int r, int c){
  return new BasicSquare(r, c, "red");
}

Square* createSquare(int r, int c, string color, string type){
  
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

int Game::calculateScore(int removeCount){
  if(removeCount > 2){
    return ((removeCount-2 > 3) ? 4 : removeCount-2)*removeCount;  
  }
  return 0;
  
}


// gameplay interactions

int Game::incrementLevel(){
  return level++;
}
int Game::decrementLevel(){
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
