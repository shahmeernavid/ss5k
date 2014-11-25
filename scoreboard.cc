#include "scoreboard.h"

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
