#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

class ScoreBoard {
    
    int score, levelScore, movesMade;

  public:
    ScoreBoard();
    void addPoints(int n);
    

    int getScore();
    int getLevelScore();
    void resetScore();
    void resetLevel();
    
    void addMoves(int n);
    void resetMoves();
};

#endif
