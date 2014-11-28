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

Game::Game():grid(NULL),level(0),settings(Settings::getInstance()){
}

Game::~Game(){
  delete grid;
}

void Game::init(istream& in, int rows){
  grid = new Grid(in, rows);
}

void Game::init(int n, int m){
  grid = new Grid(n, m);
}


int Game::setLevel(int l){
  grid->levelChanged(l);
  return level = l;
}

Grid* Game::getGrid() {
  return grid;
}


// gameplay interactions

int Game::incrementLevel(){
  return setLevel(level+1);
}
int Game::decrementLevel(){
  if(level > 0){
    return setLevel(level - 1);  
  }
  return level;
}

int Game::oppositeDirection(int z){
  if(z == 0){
    return 1;
  }
  else if(z == 1){
    return 0;
  }
  else if(z == 2){
    return 3;
  }
  else if(z == 3){
    return 2;
  }
  return -1;
}

int Game::swap(int r, int c, int z){
  bool result = grid->swap(r, c, z);
  if(result){
    
    vector<int> scores = grid->process();
    int output = 0;
    for(int i = 0; i < scores.size(); i++){
      output += pow(2, i+1)*scores[i];
    }
    if(output){
      return output;  
    }
    else{
      // swap the square back if it doesnt create a match
      grid->swap(r, c, z);
      return 0;
    }
  }
  return 0;
}

void Game::hint(){
}
void Game::scramble(){
}
void Game::reset(){
}

void Game::print(ostream& out){
  out << *grid;
}
