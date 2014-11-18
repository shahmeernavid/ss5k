#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include <vector>

class Settings{
  static Settings* instance;
  
  std::string colors[] = {"White", "Red", "Blue", "Green"};
  std::string squareTypes[] = {"Basic", "Lateral", "Upright", "Unstable", "Psychedelic"};
  

  public:
    static Settings& getInstance();
    
};

#endif