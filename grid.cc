#include <iostream>
#include <ostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <algorithm>
#include "grid.h"
#include "display/game_display.h"
#include "squares/square.h"

using namespace std;

// initialize a grid using a predefined sequence
Grid::Grid(istream& in, int rows, int l):level(l),settings(Settings::getInstance()),factory(SquareFactory::getInstance()){
  factory->reset();
  locked = map<int, bool>();
  board = vector<vector<Square*> >();
  string line;
  int cr = 0;
  int cc = 0;
  while(getline(in, line)){
    // we still have more lines
    if(line.size() && cr < rows){
      stringstream ss(line);
      board.push_back(vector<Square*>());
      char x, y, z; 
      while(ss >> x >> y >> z){
        string color = settings->getColorFromEncoding(z);
        string type = settings->getTypeFromEncoding(y);
        cerr << "TYPE: " << type << y << endl;
        board[cr].push_back(factory->createSquare(cr, cc, color, type, true));
        board[cr].back()->setGrid(this);
        if(x == 'l'){
          locked[cr*10+cc] = true;
        }
        cc++;
      }
      cr++;
      cc = 0;
    }
    else if(cr == rows){
      cerr << "LINE " << line << endl;
      factory->setSequence(line);
    }
  }
}

Grid::Grid(int n, int m, int l):level(l),settings(Settings::getInstance()),factory(SquareFactory::getInstance()){
  factory->reset();
  cerr << "creatin grid" << endl;
  locked = map<int, bool>();
  cerr << "locked grid " << locked.size() << endl;
  board = vector<vector<Square*> >(n, vector<Square*>(m, NULL));
  for(int r = n-1; r > -1; r--){
    for(int c = m-1; c > -1; c--){
      // generate random type and color
      board[r][c] = factory->generateIndependantSquare(r, c, level, *this, "", false);
      board[r][c]->setGrid(this);
      if(rand() % 100 < settings->getLockedPercent(level)*100){
        locked[r*10+c] = true;
      }
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
  if(target){
    target->mark();
  }
}

void Grid::removeRow(int r){
  cerr << "removing row" << endl;
  for(int c = 0; c < board[r].size(); c++){
    Square* target = getSquare(r, c);
    if(target){
      target->mark();
    }
  }
}

void Grid::removeCol(int c){
  cerr << "removing col" << endl;
  for(int r = 0; r < board.size(); r++){
    Square* target = getSquare(r, c);
    if(target){
      target->mark();
    }
  }
}
void Grid::removeColor(string color){
  // cerr << "removing color " << color << endl;
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      Square* target = getSquare(r, c, color);
      if(target){
        target->mark();
      }
    }
  }
}

void Grid::removeRect(int tr, int tc, int w, int h){
  for(int r = tr; r < tr+h; r++){
    for(int c = tc; c < tc+w; c++){
      Square* target = getSquare(r, c);
      if(target){
        target->mark();
      }
    }
  }
}

int Grid::purgeMarked(){
  int count = 0;
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      Square* target = getSquare(r, c);
      if(target && target->isMarked()){
        board[r][c] = NULL;
        delete target;
        count++;
      }
    }
  }
  return count;
}

Square* Grid::getSquare(int r, int c) const{
  if(r < 0 || c < 0 || r >= board.size() || c >= board[r].size()){
    return NULL;
  }
  return board.at(r).at(c);
}

// of the square doesnt match the color, return NULL
Square* Grid::getSquare(int r, int c, string color) const{
  if(r < 0 || c < 0 || r >= board.size() || c >= board[r].size() || 
      !board[r][c] || board[r][c]->getColor() != color){

    return NULL;
  }
  return board.at(r).at(c);
}

int Grid::numRooted(){
  int output = 0;
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c  < board[r].size(); c++){
      Square* target = getSquare(r, c);
      if(target){
        output+=(target->getType() == "root") ? 1 : 0;
      }
    }
  }
  return output;
}

int Grid::numLocked(){
  return locked.size();
}

bool Grid::isLocked(int r, int c){
  return locked[r*10+c];
}
// cell removes itself
// we identify matches

vector<int> Grid::process(GameDisplay* d){
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
            vector<Square*> pendingRemove = patterns[p]->check(r, c, *this);
            // if the current square creates a pattern
            // if at least one square was removed
            if(pendingRemove.size()){
              
              string color = pendingRemove[0]->getColor();
              for(int i = 0; i< pendingRemove.size(); i++){
                if(isLocked(pendingRemove[i]->getRow(), pendingRemove[i]->getCol())){
                  locked[r*10+c] = false;
                } 
                // cerr << "removing " << pendingRemove[i]->getRow() << " " << pendingRemove[i]->getCol() << endl;
                // cerr << "color: " << pendingRemove[i]->getColor() << endl;
                pendingRemove[i]->remove(pendingRemove.size());  
              }

              int removeCount = purgeMarked();
              // add to the loop count
              loopCount += settings->calculateScore(removeCount);
              pair<int, int> coord = patterns[p]->newPos(r, c);
              int nr = coord.first;
              int nc = coord.second;
              string nt = patterns[p]->newType(); 
              if(nr > -1 && nc > -1 && nt.size()){
                toAdd.push_back(factory->createSquare(nr, nc, color, nt, true));
                toAdd.back()->setGrid(this);  
              }
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
      loopCount = 0;
    }

    if(d && scores.size() != oldLength){
      d->update(false);
    }

    for(int i = 0; i < toAdd.size(); i++){
      board[toAdd[i]->getRow()][toAdd[i]->getCol()] = toAdd[i];
    }
    
    cerr << "this" << endl;
    cerr << *this << endl;

    if(d && scores.size() != oldLength){
      d->update(false);
    }

    // fill all the holes!
    // called once more than we need it
    // can result in infinite chains
    collapse();

    if(d && scores.size() != oldLength){
      d->update(false);
    }

    fill();

    if(d && scores.size() != oldLength){
      d->update(false);
    }
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
    vector<Square*> result = patterns[i]->check(r, c, *this);
    if(result.size()){
      output =  true;
      break;
    }
  }
  // delete the temp square
  delete board[r][c];
  // restore orignal state of the board
  board[r][c] = holder;
  return output;
}

void Grid::scramble(){
  vector<Square*> linear;
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board.size(); c++){
      linear.push_back(getSquare(r, c));
    }
  }

  // shuffle
  random_shuffle(linear.begin(), linear.end());

  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board.size(); c++){
      board[r][c] = linear.back();
      linear.pop_back();
      if(board[r][c]){
        board[r][c]->setRow(r);
        board[r][c]->setCol(c);
      }
    }
  }
}

int Grid::match(int r, int c){
  vector<Pattern*> patterns = settings->getPatterns(level);
  for(int i = 0; i < 4; i++){
    
    swap(r, c, i);
    int out = -1;
    for(int p = 0; p < patterns.size(); p++){
      vector<Square*> results = patterns[p]->check(r, c, *this);
      if(results.size()){
        out = i;
      }
    }
    swap(r, c, i);
    if(out!=-1){
      return out;
    }
  }
  return -1;
}

int Grid::hint(){
  
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      int z = match(r, c);
      if(z != -1){
        return r*100 + c*10 + z;
      }
    }
  }
  cerr << "HINTING" << endl;
  return -1;
}

void Grid::fill(){
  // create new squares to fill holes
  // locality of reference!
  for(int r = 0; r < board.size(); r++){
    for(int c = 0; c < board[r].size(); c++){
      if(getSquare(r, c) == NULL){
        board[r][c] = factory->generateIndependantSquare(r, c, level, *this, "", true);
        // remember to set grid!
        board[r][c]->setGrid(this);  
      }
    }
  }

  cerr << "Filled" << endl;
  cerr << *this << endl;
  cerr << "---------------" << endl;
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
  cerr << "---------------" << endl;
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
  if(tr > -1 && tc > -1 && tr < board.size() && tc < board[tr].size() && r > -1 && c > -1 
    && tr < board.size() && tc < board[tr].size()){
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
        Square* target = getSquare(r, c);
        if(target){
          target->draw(window, c * Settings::SQUARE_WIDTH, r * Settings::SQUARE_HEIGHT);
        }
        else{
          Square::drawEmptySquare(window, c * Settings::SQUARE_WIDTH, r * Settings::SQUARE_HEIGHT);
        }
      }
  }
}

ostream& operator<<(ostream& out, Grid& grid){
  for(int r = 0; r < grid.board.size(); r++){
    for(int c = 0; c < grid.board[r].size(); c++){
      Square* s = grid.getSquare(r, c); 
      if(s){
        out << ((grid.isLocked(r, c)) ? "l" : "_");
        out << *s;
        
      }
      else{
        out << ((grid.isLocked(r, c)) ? "l" : "_");
        out << "__";
        
      }
      out << " ";
    }
    out << endl;
  }
  return out;
}

int Grid::getLevel(){
  return level;
}


