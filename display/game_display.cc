#include <iostream>
#include "game_display.h"
#include "../game.h"
#include <unistd.h>

using namespace std;

void GameDisplay::updateTextDisplay() {

    // output score information (make this prettier)
    out << "Level: " << game->getLevel() << endl;
    ScoreBoard *sb = game->getScoreBoard();
    out << "Level Score: " << sb->getLevelScore() << endl;
    out << "Total Score: " << sb->getScore() << endl;

    game->print(out);

    out << "-----------------------" << endl;
}

GameDisplay::GameDisplay(Game* game, ostream& out) :
    game(game),
    w(NULL),
    out(out)
    { }

GameDisplay::~GameDisplay() {
    delete w;
}

void GameDisplay::updateWindowDisplay() {

    game->drawSquares(w);
}


void GameDisplay::output(std::string t){
    out << t << endl;
}

void GameDisplay::update(bool text) {
    if(text){
        updateTextDisplay();    
    }
    

    // update the text display and graphics display, if we have one
    if (w) {
        updateWindowDisplay();
        usleep(1000);
    }
}

void GameDisplay::createWindow() {
    w = new Xwindow();
}
