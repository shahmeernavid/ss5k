#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include <vector>

class Settings{
  static Settings* instance;

  public:
    static Settings& getInstance();
    
};

#endif