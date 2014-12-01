#include "settings.h"
#include "patterns/basic.h"
#include "patterns/fourhorizontal.h"
#include "patterns/fourvertical.h"
#include "patterns/fivehorizontal.h"
#include "patterns/fivevertical.h"
#include "patterns/l1.h"
#include "patterns/l2.h"
#include "patterns/l3.h"
#include "patterns/l4.h"
#include "patterns/t1.h"
#include "patterns/t2.h"
#include "patterns/t3.h"
#include "patterns/t4.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Settings* Settings::instance = NULL;
int Settings::WINDOW_HEIGHT = 550; 
int Settings::WINDOW_WIDTH = 500; 
int Settings::GRID_ROWS = 10; 
int Settings::GRID_COLS = 10; 
int Settings::STATUS_BAR_HEIGHT = 50;
int Settings::SQUARE_HEIGHT = (Settings::WINDOW_HEIGHT - Settings::STATUS_BAR_HEIGHT) / Settings::GRID_ROWS; 
int Settings::SQUARE_WIDTH = Settings::WINDOW_WIDTH / Settings::GRID_COLS; 

Settings const* Settings::getInstance(){
  if(!instance){
    instance = new Settings();
    atexit(clean);
  }
  return instance;
}


void Settings::clean(){
  delete instance;
}

Settings::Settings(){
  // configure everything here
  registerLevel(new LevelSettings(), 0);
  levels[0]->addColor("red", .25);
  levels[0]->addColor("blue", .25);
  levels[0]->addColor("green", .25);
  levels[0]->addColor("white", .25);

  levels[0]->addType("basic", .96);
  levels[0]->addType("lateral", .01);
  levels[0]->addType("upright", .01);
  levels[0]->addType("unstable", .01);
  levels[0]->addType("psychedelic", .01);

  levels[0]->setLevelUpScore(30);
  levels[0]->setInputFile("sequence.txt");
///////////////////////

  registerLevel(new LevelSettings(), 1);
  levels[1]->addColor("red", .33);
  levels[1]->addColor("blue", .17);
  levels[1]->addColor("green", .17);
  levels[1]->addColor("white", .33);

  levels[1]->addType("basic", .2);
  levels[1]->addType("lateral", .2);
  levels[1]->addType("upright", .2);
  levels[1]->addType("unstable", .2);
  levels[1]->addType("psychedelic", .2);

  levels[1]->setLevelUpScore(300);
  levels[1]->setSpecialCount(5);
///////////////////////

  registerLevel(new LevelSettings(), 2);
  levels[2]->addColor("red", .25);
  levels[2]->addColor("blue", .25);
  levels[2]->addColor("green", .25);
  levels[2]->addColor("white", .25);

  levels[2]->addType("basic", 1);
  levels[2]->addType("lateral", 0);
  levels[2]->addType("upright", 0);
  levels[2]->addType("unstable", 0);
  levels[2]->addType("psychedelic", 0);

  levels[2]->setLevelUpScore(50);
  levels[2]->setLockedCellsPercent(.2);

  /////////////////////////

  registerLevel(new LevelSettings(), 3);
  levels[3]->addColor("red", .25);
  levels[3]->addColor("blue", .25);
  levels[3]->addColor("green", .25);
  levels[3]->addColor("white", .25);

  levels[3]->addType("basic", 1);
  levels[3]->addType("lateral", 0);
  levels[3]->addType("upright", 0);
  levels[3]->addType("unstable", 0);
  levels[3]->addType("psychedelic", 0);
  levels[3]->addType("root", 0);

  levels[3]->setLevelUpScore(1000);
  levels[3]->setLockedCellsPercent(.2);
  levels[3]->setMaxMoves(50);
  levels[3]->setInputFile("sequence3.txt");
  levels[3]->registerPattern(new T1Pattern(-1));
  levels[3]->registerPattern(new T2Pattern(-2));
  levels[3]->registerPattern(new T3Pattern(-3));
  levels[3]->registerPattern(new T4Pattern(-4));

  /////////////////////////

  colorEncodings["red"] = '1';
  colorEncodings["white"] = '0';
  colorEncodings["blue"] = '3';
  colorEncodings["green"] = '2';
  typeEncodings["basic"] = '_';
  typeEncodings["lateral"] = 'h';
  typeEncodings["upright"] = 'v';
  typeEncodings["unstable"] = 'b';
  typeEncodings["psychedelic"] = 'p';
  typeEncodings["root"] = 'r';

  registerPattern(new BasicPattern(8));
  registerPattern(new FourHorizontalPattern(7));
  registerPattern(new FourVerticalPattern(6));
  registerPattern(new FiveHorizontalPattern(5));
  registerPattern(new FiveVerticalPattern(4));
  registerPattern(new L1Pattern(3));
  registerPattern(new L2Pattern(2));
  registerPattern(new L3Pattern(1));
  registerPattern(new L4Pattern(0));
  

}
Settings::~Settings(){
  for(map<int, LevelSettings*>::iterator i = levels.begin(); i != levels.end(); i++){
    delete i->second;
  }
}

int Settings::numLevels() const{
  return levels.size();
}

// l = -1 means global settings
void Settings::registerPattern(Pattern* p, int level){
  if(level == -1){
    for(int i = 0; i < levels.size(); i++){
      Pattern* copy = p->copy();
      levels[i]->registerPattern(copy);
    }
    // we dont want a memory leak!
    delete p;
  }
  else if(level > -1){
    levels[level]->registerPattern(p);
  }
}

int Settings::getMaxMoves(int l) const{
  return levels.at(l)->getMaxMoves();
}

void Settings::registerLevel(LevelSettings* ls, int level){
  levels[level] = ls;
}
void Settings::addType(string name, double probability, int l){
  if(l == -1){
    for(int i = 0; i < levels.size(); i++){
      levels[i]->addType(name, probability);
    }
  }
  else if(l > -1){
    levels[l]->addType(name, probability);
  }
}
void Settings::addColor(string name, double probability, int l){
  if(l == -1){
    for(int i = 0; i < levels.size(); i++){
      levels[i]->addColor(name, probability);
    }
  }
  else if(l > -1){
    levels[l]->addColor(name, probability);
  }
}

vector<string> Settings::getSquareColors(int l) const{
  return levels.at(l)->getColors();
}

vector<string> Settings::getSquareTypes(int l) const{
  return levels.at(l)->getTypes();
}

char Settings::getTypeEncoding(string type) const{
  return typeEncodings.at(type);
}

char Settings::getColorEncoding(string color) const{
  return colorEncodings.at(color);
}

double Settings::getTypeProbability(string type, int l) const{
  return levels.at(l)->getTypeProbability(type); 
}

double Settings::getColorProbability(string color, int l) const{
  return levels.at(l)->getColorProbability(color);
}

map<string, double> Settings::getTypeProbabilities(int l) const{
  return levels.at(l)->getTypeProbabilities();
}
map<string, double> Settings::getColorProbabilities(int l) const{
  return levels.at(l)->getColorProbabilities();
}

vector<Pattern*> Settings::getPatterns(int l) const{
  return levels.at(l)->getPatterns();
}

int Settings::calculateScore(int removeCount) const{
  if(removeCount >= 5){
    return 3*removeCount;
  }
  else if(removeCount == 4){
    return 2*removeCount;
  }
  return removeCount;

}

int Settings::levelUpScore(int l) const{
  return levels.at(l)->getLevelUpScore();
}

int Settings::getSpecialCount(int l) const{
  return levels.at(l)->getSpecialCount(); 
}

double Settings::getLockedPercent(int l) const{
  return levels.at(l)->getLockedCellsPercent();
}

string Settings::getColorFromEncoding(char e) const{
  for(map<string, char>::const_iterator i = colorEncodings.begin(); i != colorEncodings.end(); i++){
    if(i->second == e){
      return i->first;
    }
  }
  return "";
}

string Settings::getTypeFromEncoding(char e) const{
  for(map<string, char>::const_iterator i = typeEncodings.begin(); i != typeEncodings.end(); i++){
    if(i->second == e){
      return i->first;
    }
  }
  return "";
}

string Settings::getInputFile(int l) const{
  return levels.at(l)->getInputFile();
}



