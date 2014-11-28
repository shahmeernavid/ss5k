#include <iostream>
#include "game_display.h"
#include "../game.h"

using namespace std;

void GameDisplay::updateTextDisplay() {

    // output score information (make this prettier)
    out << "Level: " << game->getLevel() << endl;
    ScoreBoard *sb = game->getScoreBoard();
    out << "Score: " << sb->getScore() << endl;
    out << "Total Score: " << sb->getLevelScore() << endl;

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

void GameDisplay::update() {

    updateTextDisplay();

    // update the text display and graphics display, if we have one
    if (w) {
        updateWindowDisplay();
    }
}

void GameDisplay::createWindow() {
    w = new Xwindow();
}
