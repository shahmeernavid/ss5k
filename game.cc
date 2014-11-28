#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
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

Game::Game():grid(NULL),level(0),settings(Settings::getInstance()),display(NULL),scoreboard(NULL){}

Game::~Game(){
  delete grid;
  delete display;
  delete scoreboard;
}

void Game::init(){
  scoreboard = new ScoreBoard();
  // creates a new grid
  reset();
}

void Game::init(istream& in, int rows){
  scoreboard = new ScoreBoard();
  grid = new Grid(in, rows, level);
}

void Game::init(int n, int m){
  scoreboard = new ScoreBoard();
  grid = new Grid(n, m, level);
}

void Game::setUpDisplay(ostream& out, bool window){
  display = new GameDisplay(this, out);
  if(window){
    display->createWindow();
  }
  display->update();
}


int Game::setLevel(int l){
  grid->levelChanged(l);
  return level = l;
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

void Game::swap(int r, int c, int z){
  bool result = grid->swap(r, c, z);
  if(result){
    
    vector<int> scores = grid->process();
    int output = 0;
    for(int i = 0; i < scores.size(); i++){
      output += pow(2, i+1)*scores[i];
    }
    if(output){
      scoreboard->addPoints(output);

      if(scoreboard->getLevelScore() > settings->levelUpScore(level)){
        scoreboard->resetLevel();
        incrementLevel();
        cerr << "here!" << endl;
        reset();
        cerr << "here2!" << endl;
        display->output("---------------------");
        display->output("Level Up!!");
        display->output("---------------------");
        cerr << "here3!" << endl;
      }  
    }
    else{
      // swap the square back if it doesnt create a match
      grid->swap(r, c, z);
    }
  }
  display->update();
}

string digitToString(int i){
  if(i == 0){
    return "0";
  }
  else if(i == 1){
    return "1";
  }
  else if(i == 2){
    return "2";
  }
  else if(i == 3){
    return "3";
  }
  else if(i == 4){
    return "4";
  }
  else if(i == 5){
    return "5";
  }
  else if(i == 6){
    return "6";
  }
  else if(i == 7){
    return "7";
  }
  else if(i == 8){
    return "8";
  }
  else if(i == 9){
    return "9";
  }
  return "";
}

string toString(int i){
  if (i == 0) return "0";
  string output = "";
  bool neg = i < 0;
  if(neg) i *= -1;
  while(i > 9){
    output = digitToString(i/10) + output;
    i /= 10;
  }
  return (neg) ? "-" + digitToString(i) + output : digitToString(i) + output;
}

void Game::hint(){
  int move = grid->hint();
  cerr << "HINT " << string(1, 5) << endl; 
  int z = move%10;
  int c = move/10%10;
  int r = move/100%10;



  display->output("Hint: " + toString(r) + " " + toString(c) + " " + toString(z));

}
void Game::scramble(){
}

void Game::reset(){
  delete grid;
  string inputFile = settings->getInputFile(level);
  if(inputFile.size()){
    ifstream file(inputFile);
    grid = new Grid(file, Settings::GRID_ROWS, level);
  }
  else{
    grid = new Grid(Settings::GRID_ROWS, Settings::GRID_COLS, level);
  }
}

void Game::print(ostream& out){
  out << *grid;
}

int Game::getLevel(){
  return level;
}

ScoreBoard* Game::getScoreBoard(){
  return scoreboard;
}

void Game::drawSquares(Xwindow* window){
  grid->drawSquares(window);
}