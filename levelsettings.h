#ifndef __LEVEL_SETTINGS_H__
#define __LEVEL_SETTINGS_H__

#include <vector>
#include <string>
#include <map>
#include "patterns/pattern.h"


class LevelSettings{
  int levelUpScore;
  // type -> encoding
  std::map<std::string, std::string> typeEncodings;
  // color -> encoding
  std::map<std::string, std::string> colorEncodings;
  // type -> probability
  std::map<std::string, double> typeProbabilities;
  // color -> probability
  std::map<std::string, double> colorProbabilities;

  std::vector<Pattern*> patterns;

  std::vector<std::string> colors;

  std::vector<std::string> types;

  public:
    LevelSettings();
    ~LevelSettings();

    void addType(std::string name, std::string encoding, double prob=-1);
    void addColor(std::string name, std::string encoding, double prob=-1);

    // accessor methods
    double getColorProbability(std::string) const;
    double getTypeProbability(std::string) const;
    std::string getColorEncoding(std::string) const;
    std::string getTypeEncoding(std::string) const;
    std::vector<std::string> getColors() const;
    std::vector<std::string> getTypes() const;
    std::vector<Pattern*> getPatterns() const;
    void registerPattern(Pattern* p);
    void setLevelUpScore(int l);
    int getLevelUpScore() const;
   
};

#endif