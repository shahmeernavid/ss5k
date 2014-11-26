#include "scoreboard.h"

ScoreBoard::ScoreBoard() :
    score(0),
    levelScore(0),
    movesMade(0)
    { }

void ScoreBoard::addPoints(int n) {
    
    score += n;
}

int ScoreBoard::getScore() {
    
    return score;
}

void ScoreBoard::resetScore() {

    score = 0;
    levelScore = 0;
}
