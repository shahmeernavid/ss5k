#include <iostream>
#include <fstream>
#include <cstdlib>
#include "grid.h"
#include "game.h"
#include "squares/square.h"
#include "scoreboard.h"
#include "display/game_display.h"

using namespace std;

Game* game = Game::getInstance();

void play(int x, int y, int z){
  game->swap(x, y, z);
  game->print(cout);
}


int main(int argc, char* args[]){
  int level = 0;
  string script = "";
  bool text = false;
  bool progress = false;
  int seed = time(NULL);
  for(int i =0; i < argc; i++){
    if(string(args[i]) == "-scriptfile"){
      script = args[i+1];
    }
    if(string(args[i]) == "-text"){
      text = true;
    }
    if(string(args[i]) == "-seed"){
      seed = atoi(args[i+1]);
    }
    if(string(args[i]) == "-startlevel"){
      level = atoi(args[i+1]);
    }
    if(string(args[i]) == "-progress"){
      progress = true;
    }
    if(string(args[i]) == "-r"){
      Settings::GRID_ROWS = atoi(args[i+1]);
      Settings::SQUARE_HEIGHT = (Settings::WINDOW_HEIGHT - Settings::STATUS_BAR_HEIGHT) / Settings::GRID_ROWS; 
      Settings::SQUARE_WIDTH = Settings::WINDOW_WIDTH / Settings::GRID_COLS; 
    }
    if(string(args[i]) == "-c"){
      Settings::GRID_COLS = atoi(args[i+1]);
      Settings::SQUARE_HEIGHT = (Settings::WINDOW_HEIGHT - Settings::STATUS_BAR_HEIGHT) / Settings::GRID_ROWS; 
      Settings::SQUARE_WIDTH = Settings::WINDOW_WIDTH / Settings::GRID_COLS; 
    }
    if(string(args[i]) == "-h"){
      Settings::WINDOW_HEIGHT = atoi(args[i+1]);
      Settings::SQUARE_HEIGHT = (Settings::WINDOW_HEIGHT - Settings::STATUS_BAR_HEIGHT) / Settings::GRID_ROWS; 
      Settings::SQUARE_WIDTH = Settings::WINDOW_WIDTH / Settings::GRID_COLS; 
    }
    if(string(args[i]) == "-w"){
      Settings::WINDOW_WIDTH = atoi(args[i+1]);
      Settings::SQUARE_HEIGHT = (Settings::WINDOW_HEIGHT - Settings::STATUS_BAR_HEIGHT) / Settings::GRID_ROWS; 
      Settings::SQUARE_WIDTH = Settings::WINDOW_WIDTH / Settings::GRID_COLS; 
    }
  }
  srand(seed);

  game->setUpDisplay(cout, !text);
  if(level >= Settings::getInstance()->numLevels()){
    cout << "-----------------" << endl;
    cout << "Level Out of Range!" << endl;
    cout << "-----------------" << endl;
    level = 0;
  }
  game->setLevel(level, true);
  if(script.size()){
    fstream file(script.c_str());
    game->init(file, Settings::GRID_ROWS);
  }
  else{
    game->init();
  }

  string cmd;

  game->start();
  
  while(cin >> cmd){
    if(cmd == "swap"){
      int x, y, z;
      cin >> x >> y >> z;
      game->swap(x, y, z, progress);
    }
    else if(cmd == "hint"){
      game->hint();
    }
    else if(cmd == "scramble"){
      game->scramble();
    }
    else if(cmd == "levelup"){
      game->incrementLevel();
      game->reset();
    }
    else if(cmd == "leveldown"){
      game->decrementLevel();
      game->reset();
    }
    else if(cmd == "restart"){
      game->reset();
    }
    else if(cmd == "print"){
      game->print(cerr);
    }
  }
}
