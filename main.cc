#include <iostream>
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
  game->init(10, 10);
  game->print(cout);


  game->swap(0, 0, 1);
  game->print(cout);
  // cerr << "done" << endl;
  //game->print(cout);

  // Grid *g = new Grid(10, 10);
  // ScoreBoard *sb = new ScoreBoard;
  // Xwindow *window = new Xwindow;

  // GameDisplay *d = new GameDisplay(g, sb);
  // d->setWindow(window);
  // d->update();

  //   int n;
  // while (cin >> n) {

  // }


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
