#include "game_display.h"

void GameDisplay::updateTextDisplay() {

}

void GameDisplay::updateWindowDisplay() {

}


void GameDisplay::update() {

    updateTextDisplay();

    // update the text display and graphics display, if we have one
    if (w) {
        updateWindowDisplay();
    }
}
