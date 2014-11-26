#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

class ScoreBoard {
    
    int score, levelScore, movesMade;

  public:
    ScoreBoard();
    void addPoints(int n);
    int getScore();
    void resetScore();
    
    void addMoves(int n);
    void resetMoves();
};

#endif
