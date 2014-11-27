#include <iostream>
#include <ostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include "grid.h"
#include "squares/square.h"

using namespace std;

// initialize a grid using a predefined sequence
Grid::Grid(istream& in):settings(Settings::getInstance()){
  while(cin){
    char x, y, z;
    cin >> x >> y >> z;
  }
}

Grid::Grid(int n, int m):numCols(m),level(0),settings(Settings::getInstance()),factory(SquareFactory::getInstance()){
  board = vector<vector<Square*> >(n, vector<Square*>(m, NULL));
  for(int r = 0; r < n; r++){
    for(int c = 0; c < m; c++){
      // generate random type and color
      board[r][c] = factory->generateSquare(r, c, level);
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

int Grid::removeRow(int r){
  int count = 0;
  for(int c = 0; c < board[r].size(); c++){
    Square* target = getSquare(r, c);
    count += (target) ? 1 : 0;
    board[r][c] = NULL;
    delete target;
  }
  return count;
}

int Grid::removeCol(int c){
  int count = 0;
  for(int r = 0; r < board[r].size(); r++){
    Square* target = getSquare(r, c);
    count += (target) ? 1 : 0;
    board[r][c] = NULL;
    delete target;
  }
  return count;
}
int Grid::removeColor(string color){
  int count = 0;
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      Square* target = getSquare(r, c, color);
      if(target){
        count++;
        board[r][c] = NULL;
        delete target;  
      }
    }
  }
  return count;
}

int Grid::removeRect(int tr, int tc, int w, int h){
  int count = 0;
  for(int r = tr; r < tr+h; r++){
    for(int c = tr; c < tc+w; c++){
      Square* target = getSquare(r, c);
      count += (target) ? 1 : 0;
      board[r][c] = NULL;
      delete target;
    }
  }
  return count; 
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
  vector<Pattern*> patterns = settings->getPatterns(level);

  // keep looking until we've found all combo matches
  while(scores.size() != oldLength){
    // # of sqares removed for this passthrough of the grid
    int loopCount = 0;
    vector<Square*> toAdd = vector<Square*>();
    // go through rows
    for(int r = 0; r < board.size(); r++){
      // go through columns
      for(int c = 0; c < board[r].size(); c++){
        Square* square = getSquare(r, c);
        if(square){
          // go through each pattern
          for(int p = 0; p < patterns.size(); p++){
            pair<vector<Square*>, pair<string, pair<int, int> > > results = patterns[p]->check(r, c, *this);
            vector<Square*> pendingRemove = results.first;
            // if the current square creates a pattern
            // if at least one square was removed
            if(pendingRemove.size()){
              string color = pendingRemove[0]->getColor();
              int removeCount = 0;
              for(int i = 0; i< pendingRemove.size(); i++){
                cerr << "removing " << pendingRemove[i]->getRow() << " " << pendingRemove[i]->getCol() << endl;
                cerr << "color: " << pendingRemove[i]->getColor() << endl;
                removeCount += pendingRemove[i]->remove();
              }
              // add to the loop count
              loopCount += settings->calculateScore(removeCount);
              int nr = results.second.second.first;
              int nc = results.second.second.second;
              string nt = results.second.first; 
              if(nr > -1 && nc > -1 && nt.size()){
                toAdd.push_back(factory->createSquare(nr, nc, color, nt));
                toAdd.back()->setGrid(this);  
              }
              // dont check for any more patterns
              break;
            }
            
          }  
        }
      }
    }

    for(int i = 0; i < toAdd.size(); i++){
      board[toAdd[i]->getRow()][toAdd[i]->getCol()] = toAdd[i];
    }
    oldLength = scores.size();
    if(loopCount > 0){
      scores.push_back(loopCount);
      loopCount = 0;
    }
    cerr << "this" << endl;
    cerr << *this << endl;
    // fill all the holes!
    // called once more than we need it
    // can result in infinite chains
    collapse();
    fill();
    //cerr << "done this loop " << loopCount << endl;

  }
  
  return scores;
}

bool Grid::match(int r, int c, string color){
  bool output = false;
  Square* holder = getSquare(r, c);
  // put in temporary square
  board[r][c] = factory->createSquare(r, c, color, "basic", false);
  board[r][c]->setGrid(this);
  vector<Pattern*> patterns = settings->getPatterns(level);
  for(int i = 0 ; i < patterns.size(); i++){
    pair<vector<Square*>, pair<string, pair<int, int> > > result = patterns[i]->check(r, c, *this);
    if(result.first.size()){
      output =  true;
    }
  }
  // delete the temp square
  delete board[r][c];
  // restore orignal state of the board
  board[r][c] = holder;
  cerr << "match: " << output << " " << r << " " << c << " " << color << endl;
  return output;
}

void Grid::fill(){
  // create new squares to fill holes
  // locality of reference!
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      if(getSquare(r, c) == NULL){
        board[r][c] = factory->generateIndependantSquare(r, c, level, *this);
        // remember to set grid!
        board[r][c]->setGrid(this);  
      }
    }
  }

  cerr << "fill" << endl;
  cerr << *this << endl;
}

void Grid::collapse(){
  // go thorugh the grid, top down
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      // if the square at index r,c is NULL
      if(getSquare(r, c) == NULL){
        // go up in the current column
        // bubble up the hole
        for(int i = r; i > -1; i--){
          // swap up
          swap(i, c, 0);
        }
      }
    }
  }

  cerr << "collapse" << endl;
  cerr << *this << endl;  
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
  if(tr > -1 && tc > -1 && tr < board.size() && tc < board[tc].size()){
    // do the swap
    Square* holder = getSquare(tr, tc);
    board[tr][tc] = getSquare(r, c);
    board[r][c] = holder;
    
    // update coordinates
    if(board[tr][tc]){
      board[tr][tc]->setRow(tr);
      board[tr][tc]->setCol(tc);  
    }
    if(board[r][c]){
      board[r][c]->setCol(c);
      board[r][c]->setRow(r);
    }

    return true;  
  }
  return false;
}

void Grid::levelChanged(int l){
  level = l;
}

void Grid::drawSquares(Xwindow *window) {

    for(int r = 0; r < board.size(); r++){
        for(int c = 0; c < board[r].size(); c++){
            getSquare(r, c)->draw(window, r * Settings::SQUARE_WIDTH, c * Settings::SQUARE_HEIGHT);
        }
    }
}

ostream& operator<<(ostream& out, Grid& grid){
  for(int r = 0; r < grid.board.size(); r++){
    for(int c = 0; c < grid.board[r].size(); c++){
      Square* s = grid.getSquare(r, c); 
      if(s){
        out << "_";
        out << *s;
        out << " ";
      }
      else{
        out << "___";
        out << " ";
      }
    }
    out << endl;
  }
  out << "----------------" << endl;
  return out;
}


