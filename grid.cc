#include <iostream>
#include <ostream>
#include <cstdlib>
#include <vector>
#include "grid.h"
#include "game.h"
#include "squares/square.h"
//#include "settings.h"

using namespace std;

// initialize a grid using a predefined sequence
Grid::Grid(istream& in, Game* g):game(g){
  
}

Grid::Grid(int n, int m, Game* g):game(g){
  board = vector<vector<Square*> >(n, vector<Square*>(m, NULL));
  for(int r = 0; r < n; r++){
    for(int c = 0; c < m; c++){
      // generate random type and color
      board[r][c] = game->generateSquare(r, c);
      board[r][c]->setGrid(this);
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


int Grid::remove(int r, int c){
  Square* target = getSquare(r, c);
  board[r][c] = NULL;
  delete target;
  return 1;
}

Square* Grid::getSquare(int r, int c){
  if(r < 0 || c < 0 || r >= board.size() || c >= board[r].size()){
    return NULL;
  }
  return board[r][c];
}

// of the square doesnt match the color, return NULL
Square* Grid::getSquare(int r, int c, string color){
  if(r < 0 || c < 0 || r >= board.size() || c >= board[r].size() || 
      !board[r][c] || board[r][c]->getColor() != color){

    return NULL;
  }
  return board[r][c];
}

// cell removes itself
// we identify matches

vector<int> Grid::process(){
  vector<int> scores;
  int oldLength = -1;
  vector<Pattern*> patterns = game->getPatterns();
  // keep looking until we've found all combo matches
  while(scores.size() != oldLength){
    // # of sqares removed for this passthrough of the grid
    int loopCount = 0;
    // go through rows
    for(int r = 0; r < board.size(); r++){
      // go through columns
      for(int c = 0; c < board[r].size(); c++){
        Square* square = getSquare(r, c);
        if(square){
          // go through each pattern
          for(int p = 0; p < patterns.size(); p++){
            vector<Square*> results = patterns[p]->check(r, c, *this);
            // if the current square creates a pattern
            // if at least one square was removed
            if(results.size()){
              int removeCount = 0;
              for(int i = 0; i< results.size(); i++){
                removeCount += results[i]->remove();
              }
              // add to the loop count
              loopCount += game->calculateScore(removeCount);
              // dont check for any more patterns
              break;
            }
          }  
        }
      }
    }
    oldLength = scores.size();
    if(loopCount > 0){
      scores.push_back(loopCount);
    }
    // fill all the holes!
    // collapse();
  }
  
  return scores;
}

bool Grid::swap(int r, int c, int z){
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
  if(holder){
    board[tr][tc] = getSquare(r, c);
    board[r][c] = holder;
    return true;
  }
  return false;
}

ostream& operator<<(ostream& out, Grid& grid){
  for(int r = 0; r < grid.board.size(); r++){
    for(int c = 0; c < grid.board[r].size(); c++){
      Square* s = grid.getSquare(r, c); 
      if(s){
        out << *s;
      }
      else{
        out << "___";
      }
    }
    out << endl;
  }
  return out;
}


