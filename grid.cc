#include <iostream>
#include <ostream>
#include <cstdlib>
#include <vector>
#include "grid.h"
//#include "settings.h"

using namespace std;

Grid* Grid::instance = NULL;

Grid::Grid(int n, int m, Level* l):level(l){
  board = vector<vector<Square*> >(n, vector<Square*>(m, NULL));
  for(int r = 0; r < n; r++){
    for(int c = 0; c < m; c++){
      // generate random type and color
      map<string, string> squareInfo = level->generateSquare();
      board[r][c] = new Square(r, c, squareInfo["color"], squareInfo["type"], this);
    }
  }
}

Grid::~Grid(){
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      delete board[r][c];  
    }
  }
}


void Grid::remove(int r, int c){
  Square* target = getSquare(r, c);
  board[r][c] = NULL;
  delete target;
}

void Grid::clean(){
  delete instance;
}

Grid* Grid::getInstance(int n, int m, Level* l){
  if(!instance){
    instance = new Grid(n, m, l);
    atexit(clean);
  }
  return instance;
}

Square* Grid::getSquare(int r, int c){
  if(r < 0 || c < 0 || r > board.size() || c > board[0].size()){
    return NULL;
  }
  return board[r][c];
}

Square* Grid::getSquare(int r, int c, string color){
  if(r < 0 || c < 0 || r > board.size() || c > board[0].size() || board[r][c]->getColor() != color){
    return NULL;
  }
  return board[r][c];
}

// cell removes itself
// we identify matches

int Grid::processSwap(){
  vector<int> scores;
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      vector<Pattern*> patterns = level->getPatterns();
      for(int p = 0; p < patterns.size(); p++){
        if(patterns[p]->check(r, c, *this)){
          scores.push_back(getSquare(r, c)->remove());
          // dont check for any more patterns
          break;
        }
      }
    }
  }
  int output = 0;
  for(int i = 0; i < scores.size(); i++){
    output += scores[i];
  }
  return output;
}

int Grid::swap(int r, int c, int z){
  // 0 -> north
  // 1 -> south
  // 2 -> west
  // 3 -> east
  int tr = r, tc = c;
  if(z == 0){
    tr--;
  }
  else if(z == 1){
    tr++;
  }
  else if(z == 2){
    tc--;
  }
  else if(z == 3){
    tc++;
  }

  Square* holder = getSquare(tr, tc);
  int result = 0;
  if(holder){
    board[tr][tc] = getSquare(r, c);
    board[r][c] = holder;
    result = processSwap();
    if(result){
      return result;
    }
    else{
      board[r][c] = getSquare(tr, tc);
      board[tr][tc] = holder;
    }
  }

  return 0;
}

ostream& operator<<(ostream& out, Grid& grid){
  for(int r = 0; r < grid.board.size(); r++){
    for(int c = 0; c < grid.board[r].size(); c++){
      out << *grid.getSquare(r, c) << " ";
    }
    out << endl;
  }
  return out;
}


