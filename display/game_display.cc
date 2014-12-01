#include <iostream>
#include "game_display.h"
#include "../game.h"
#include <unistd.h>
#include <string>
#include <sstream>
#include <climits>

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
    sb(game->getScoreBoard()),
    out(out),
    w(NULL)
    { }

GameDisplay::~GameDisplay() {
    delete w;
}

void GameDisplay::updateWindowDisplay() {

    game->drawSquares(w);

    int status_bar_y = Settings::WINDOW_HEIGHT - (Settings::STATUS_BAR_HEIGHT / 2);
    stringstream score;
    stringstream level_score;
    stringstream level;

    score << "Score: " << sb->getScore();
    level_score << "Level Score: " << sb->getLevelScore();
    level << "Level: " << game->getLevel();

    // add background for status bar (covers up old strings)
    w->fillRectangle(0, Settings::WINDOW_HEIGHT - Settings::STATUS_BAR_HEIGHT, 
    Settings::WINDOW_WIDTH, Settings::STATUS_BAR_HEIGHT, 0);

    // for levels 0, 1, or 2 there is no move limit, so we do not display it
    if (game->movesLeft() == 1000) {
        // print out score/moves info
        w->drawString(5, status_bar_y, score.str(), 1);
        w->drawString(Settings::WINDOW_WIDTH / 2 - 50, status_bar_y, level_score.str(), 1);
        w->drawString(Settings::WINDOW_WIDTH - 50, status_bar_y, level.str(), 1);
    } else {
        stringstream moves;
        moves << "Moves left: " << game->movesLeft();

        w->drawString(5, status_bar_y - 7, score.str(), 1);
        w->drawString(5, status_bar_y + 7, level_score.str(), 1);
        w->drawString(Settings::WINDOW_WIDTH / 4 * 3 - 50, status_bar_y, moves.str(), 1);
        w->drawString(Settings::WINDOW_WIDTH - 50, status_bar_y, level.str(), 1);
    }
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
      // usleep(1000);
    }
}

void GameDisplay::createWindow() {
    w = new Xwindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
}
