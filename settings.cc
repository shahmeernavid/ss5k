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
#include <iostream>
#include <cstdlib>

using namespace std;

Settings* Settings::instance = NULL;

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
  // registerLevel(new LevelSettings(), 0);
  // levels[0]->addColor("red", .25);
  // levels[0]->addColor("blue", .25);
  // levels[0]->addColor("green", .25);
  // levels[0]->addColor("white", .25);

  // levels[0]->addType("basic", .96);
  // levels[0]->addType("lateral", .01);
  // levels[0]->addType("upright", .01);
  // levels[0]->addType("unstable", .01);
  // levels[0]->addType("psychedelic", .01);

  // levels[0]->setLevelUpScore(30);
  // levels[0]->setInputFile("sequence.txt");
///////////////////////

  // registerLevel(new LevelSettings(), 0);
  // levels[0]->addColor("red", .33);
  // levels[0]->addColor("blue", .17);
  // levels[0]->addColor("green", .17);
  // levels[0]->addColor("white", .33);

  // levels[0]->addType("basic", .2);
  // levels[0]->addType("lateral", .2);
  // levels[0]->addType("upright", .2);
  // levels[0]->addType("unstable", .2);
  // levels[0]->addType("psychedelic", .2);

  // levels[0]->setLevelUpScore(300);
  // levels[0]->setSpecialCount(5);
///////////////////////

  registerLevel(new LevelSettings(), 0);
  levels[0]->addColor("red", .25);
  levels[0]->addColor("blue", .25);
  levels[0]->addColor("green", .25);
  levels[0]->addColor("white", .25);

  levels[0]->addType("basic", 1);
  levels[0]->addType("lateral", 0);
  levels[0]->addType("upright", 0);
  levels[0]->addType("unstable", 0);
  levels[0]->addType("psychedelic", 0);

  levels[0]->setLevelUpScore(500);
  levels[0]->setLockedCellsPercent(.2);

  colorEncodings["red"] = '1';
  colorEncodings["white"] = '0';
  colorEncodings["blue"] = '3';
  colorEncodings["green"] = '2';
  typeEncodings["basic"] = '_';
  typeEncodings["lateral"] = 'h';
  typeEncodings["upright"] = 'v';
  typeEncodings["unstable"] = 'b';
  typeEncodings["psychedelic"] = 'p';

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
  for(int i = 0; i < levels.size(); i++){
    delete levels[i];
  }
}

// l = -1 means global settings
void Settings::registerPattern(Pattern* p, int level){
  if(level == -1){
    for(int i = 0; i < levels.size(); i++){
      Pattern* copy = p->copy();
      levels[i]->registerPattern(copy);
    }
  }
  else if(level > -1){
    levels[level]->registerPattern(p);
  }
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
  vector<string> colors = getSquareColors();
  for(int i = 0; i < colors.size(); i++){
    if(colorEncodings.at(colors[i]) == e){
      return colors[i];
    }
  }
  return "";
}

string Settings::getTypeFromEncoding(char e) const{
  vector<string> types = getSquareTypes();
  for(int i = 0; i < types.size(); i++){
    if(typeEncodings.at(types[i]) == e){
      return types[i];
    }
  }
  return "";
}

string Settings::getInputFile(int l) const{
  return levels.at(l)->getInputFile();
}



