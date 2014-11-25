#include <iostream>
#include "grid.h"
#include "game.h"
#include "squares/square.h"

using namespace std;

Game* game = Game::getInstance();

void play(int x, int y, int z){
  game->swap(x, y, z);
  game->print(cout);
}


int main(int argc, char* args[]){
  game->init(10, 10);
  game->print(cout);


  // game->swap(0, 0, 1);
  // cerr << "done" << endl;
  game->print(cout);


  // string cmd;
  
  // while(cin >> cmd){
  //   if(cmd == "swap"){
  //     int x, y, z;
  //     cin >> x >> y >> z;
  //   }
  //   else if(cmd == "hint"){
  //     // game->hint();
  //   }
  //   else if(cmd == "scramble"){
  //     // game->shuffle();
  //   }
  //   else if(cmd == "levelup"){
  //     game->incrementLevel();
  //   }
  //   else if(cmd == "leveldown"){
  //     game->decrementLevel();
  //   }
  //   else if(cmd == "restart"){
  //     // game->restart();
  //   }
  // }

  // delete game;
}
