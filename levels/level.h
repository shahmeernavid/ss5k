#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <vector>
#include <string>

class Level {
    int dropRates[4];
    bool hasSpecials;
    // to track when special blocks need to be dropped every X blocks
    int specialTimer;
  public:
    bool hasLocks; 
    vector<string, string> nextSquare();
};

#endif
