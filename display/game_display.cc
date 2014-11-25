#include <iostream>
#include "game_display.h"

using namespace std;

void GameDisplay::updateTextDisplay() {

    // output score information (make this prettier)
    (*out) << "Score: " << sb->getScore() << endl;

    (*out) << (*theGrid);
}

GameDisplay::GameDisplay(Grid *theGrid, ScoreBoard *sb) :
    theGrid(theGrid),
    sb(sb)
    { }

void GameDisplay::updateWindowDisplay() {

}


void GameDisplay::update() {

    updateTextDisplay();

    // update the text display and graphics display, if we have one
    if (w) {
        updateWindowDisplay();
    }
}
