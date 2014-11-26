#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include <cstdlib>
#include "levelsettings.h"

class Pattern;

class Settings{


  std::map<int, LevelSettings*> levels;

  static Settings* instance;

  Settings();
  ~Settings();

  void registerPattern(Pattern* p, int level = -1);
  void registerLevel(LevelSettings* ls, int level = -1);
  // l = -1 maps to global type
  void addType(std::string name, std::string encoding, double probability, int l = -1);
  void addColor(std::string name, std::string encoding, double probability, int l = -1);


  public:
    // returns a const pointer
    // ie: data cant be modified
    static Settings const * getInstance();
    static void clean();
    

    // accessors
    // defaults to get value for level 0
    std::vector<std::string> getSquareColors(int l = 0) const;
    std::vector<std::string> getSquareTypes(int l = 0) const;

    std::string getTypeEncoding(std::string type, int l = 0) const;
    std::string getColorEncoding(std::string color, int l = 0) const;

    double getTypeProbability(std::string type, int l = 0) const;
    double getColorProbability(std::string color, int l = 0) const;
    std::map<std::string, double> getTypeProbabilities(int l = 0) const;
    std::map<std::string, double> getColorProbabilities(int l = 0) const;

    std::vector<Pattern*> getPatterns(int l = 0) const;

    int calculateScore(int removeCount) const;

    int levelUpScore(int l = 0) const;
    int getSpecialCount(int l = 0) const;

    
};

#endif
