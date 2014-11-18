#include <cstdlib>
#include "grid.h"
//#include "settings.h"

using namespace std;

Grid* Grid::instance = NULL;

Grid::Grid(int n, int m){
  for(int r = 0; r < n; r++){
    for(int c = 0; c < m; c++){
      // generate random type and color
      // string color = Settings.colors[rand() % Settings.numColors];
      // string type = Settings.squareTypes[rand() % Settings.numTypes];
      board[r][c] = new Square(r, c, "Red", "White");
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

void Grid::clean(){
  delete instance;
}

Grid& Grid::getInstance(){
  if(!instance){
    instance = new Grid(10, 10);
    atexit(clean);
  }
  return *instance;
}

Square* Grid::getSquare(int r, int c){
  if(r < 0 || c < 0 || r > board.size() || c > board[0].size()){
    return NULL;
  }
  return board[r][c];
}

int Grid::move(int r, int c, int z){
  // 0 -> north
  // 1 -> south
  // 2 -> west
  // 3 -> east
  int tr = r, tc = c;



  // Square* holder = board[r + z][c]



  return 0;
}

