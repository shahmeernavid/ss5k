#include "display.h"

void Display::notify() {

    // update the text display and graphics display, if we have one
    if (td) {
        td->printGrid();
    }

    if (w) {
        w->printGrid();
    }
}
