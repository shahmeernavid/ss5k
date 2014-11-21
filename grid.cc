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
  while(cin){
    char x, y, z;
    cin >> x >> y >> z;
  }
}

Grid::Grid(int n, int m, Game* g):game(g), numCols(m){
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
  if(target){
    board[r][c] = NULL;
    delete target;
    return 1;  
  }
  
  return 0;
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
    // called once more than we need it
    // can result in infinite chains
    collapse();
    cerr << "done" << endl;
    cerr << *this << endl;
  }
  
  return scores;
}



void Grid::collapse(){
  vector<int> holes = vector<int>(board[0].size(), 0);
  // go thorugh the grid, top down
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      // if the square at index r,c is NULL
      if(getSquare(r, c) == NULL){
        // keep track of how many holes each column has
        holes[c]++;
        // go up in the current column
        // bubble up the hole
        for(int i = c-1; i > 0; i--){
          // swap down
          swap(r, i, 1);
        }
      }
    }
  }

  // create new squares to fill holes
  // locality of reference!
  for(int c = 0; c < holes.size(); c++){
    for(int r = 0; r < board.size(); r++){
      board[r][c] = game->generateSquare(r, c);
      // remember to set grid!
      board[r][c]->setGrid(this);
    }
  }
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


