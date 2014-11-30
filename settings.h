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
  // type -> encoding
  std::map<std::string, char> typeEncodings;
  // color -> encoding (int)
  std::map<std::string, char> colorEncodings;

  static Settings* instance;

  Settings();
  ~Settings();

  void registerPattern(Pattern* p, int level = -1);
  void registerLevel(LevelSettings* ls, int level = -1);
  // l = -1 maps to global type
  void addType(std::string name, double probability, int l = -1);
  void addColor(std::string name, double probability, int l = -1);


  public:
    // returns a const pointer
    // ie: data cant be modified
    static Settings const * getInstance();
    static void clean();
    

    // accessors
    // defaults to get value for level 0
    std::vector<std::string> getSquareColors(int l = 0) const;
    std::vector<std::string> getSquareTypes(int l = 0) const;

    char getTypeEncoding(std::string type) const;
    char getColorEncoding(std::string color) const;
    std::string getColorFromEncoding(char e) const;
    std::string getTypeFromEncoding(char e) const;

    double getTypeProbability(std::string type, int l = 0) const;
    double getColorProbability(std::string color, int l = 0) const;
    std::map<std::string, double> getTypeProbabilities(int l = 0) const;
    std::map<std::string, double> getColorProbabilities(int l = 0) const;

    std::vector<Pattern*> getPatterns(int l = 0) const;

    int calculateScore(int removeCount) const;

    int numLevels() const;
    int getMaxMoves(int l) const;

    int levelUpScore(int l = 0) const;
    double getLockedPercent(int l = 0) const;
    int getSpecialCount(int l = 0) const;
    std::string getInputFile(int l = 0) const;
    
    // these are used to draw the graphical display
    static const int WINDOW_HEIGHT = 550; 
    static const int WINDOW_WIDTH = 500; 
    static const int GRID_ROWS = 10; 
    static const int GRID_COLS = 10; 
    static const int STATUS_BAR_HEIGHT = 50;
    static const int SQUARE_HEIGHT = (WINDOW_HEIGHT - STATUS_BAR_HEIGHT) / GRID_ROWS; 
    static const int SQUARE_WIDTH = WINDOW_WIDTH / GRID_COLS; 

    
};

#endif
