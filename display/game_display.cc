#include <iostream>
#include "game_display.h"
#include "../game.h"
#include <unistd.h>
#include <string>
#include <sstream>

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

GameDisplay::GameDisplay(Game* game, ScoreBoard *sb, ostream& out) :
    game(game),
    sb(sb),
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
    w->drawString(5, status_bar_y, score.str(), 1);
    w->drawString(Settings::WINDOW_WIDTH / 2 - 50, status_bar_y, level_score.str(), 1);
    w->drawString(Settings::WINDOW_WIDTH - 50, status_bar_y, level.str(), 1);
}


void GameDisplay::output(std::string t){
    out << t << endl;
}

void GameDisplay::update() {

    updateTextDisplay();

    // update the text display and graphics display, if we have one
    if (w) {
        updateWindowDisplay();
        usleep(1000*500);
    }
}

void GameDisplay::createWindow() {
    w = new Xwindow(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT);
}
