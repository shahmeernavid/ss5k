#include "settings.h"
#include "patterns/basic.h"
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
  registerLevel(new LevelSettings(), 0);
  registerLevel(new LevelSettings(), 1);
  registerLevel(new LevelSettings(), 2);
  
  registerPattern(new BasicPattern(0), -1);
  addType("basic", "_", -1, -1);
  addColor("red", "1", -1, -1);

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
void Settings::addType(string name, string encoding, double probability, int l){
  if(l == -1){
    for(int i = 0; i < levels.size(); i++){
      levels[i]->addType(name, encoding, probability);
    }
  }
  else if(l > -1){
    levels[l]->addType(name, encoding, probability);
  }
}
void Settings::addColor(string name, string encoding, double probability, int l){
  if(l == -1){
    for(int i = 0; i < levels.size(); i++){
      levels[i]->addColor(name, encoding, probability);
    }
  }
  else if(l > -1){
    levels[l]->addColor(name, encoding, probability);
  }
}

vector<string> Settings::getSquareColors(int l) const{
  return levels.at(l)->getColors();
}

vector<string> Settings::getSquareTypes(int l) const{
  return levels.at(l)->getTypes();
}

string Settings::getTypeEncoding(string type, int l) const{
  return levels.at(l)->getTypeEncoding(type);
}

string Settings::getColorEncoding(string color, int l) const{
  return levels.at(l)->getColorEncoding(color);
}

double Settings::getTypeProbability(string type, int l) const{
  return levels.at(l)->getTypeProbability(type); 
}

double Settings::getColorProbability(string color, int l) const{
  return levels.at(l)->getColorProbability(color);
}

vector<Pattern*> Settings::getPatterns(int l) const{
  cerr << "key: " << l << endl;
  return levels.at(l)->getPatterns();
}

int Settings::calculateScore(int removeCount) const{
  return removeCount;
}

int Settings::levelUpScore(int l) const{
  return levels.at(l)->getLevelUpScore();
}



