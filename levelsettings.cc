#include "levelsettings.h"
#include <iostream>

using namespace std;

LevelSettings::LevelSettings():patterns(vector<Pattern*>(0)){
}

LevelSettings::~LevelSettings(){
  for(int i =0; i < patterns.size(); i++){
    delete patterns[i];
  }
}

void LevelSettings::addType(string name, string encoding, double prob){
  types.push_back(name);
  typeEncodings[name] = encoding;
  typeProbabilities[name] = prob;
}
void LevelSettings::addColor(string name, string encoding, double prob){
  colors.push_back(name);
  colorEncodings[name] = encoding;
  colorProbabilities[name] = prob;
}

// accessor methods
double LevelSettings::getColorProbability(string name) const{
  return colorProbabilities.at(name);
}
double LevelSettings::getTypeProbability(string name) const{
  return typeProbabilities.at(name);
}
string LevelSettings::getColorEncoding(string name) const{
  return colorEncodings.at(name);
}
string LevelSettings::getTypeEncoding(string name) const{
  return typeEncodings.at(name);
}
vector<string> LevelSettings::getColors() const{
  return colors;
}
vector<string> LevelSettings::getTypes() const{
  return types;
}

vector<Pattern*> LevelSettings::getPatterns() const{
  return patterns;
}

void LevelSettings::registerPattern(Pattern* p){
  for(int i = 0; i < patterns.size(); i++){
    if(patterns[i]->getPriority() > p->getPriority()){
      patterns.insert(patterns.begin()+i, p);
      return;
    }
  }
  // if we dont insert, then just push
  patterns.push_back(p);  
}

void LevelSettings::setLevelUpScore(int l){
  levelUpScore = l;
}

int LevelSettings::getLevelUpScore() const{
  return levelUpScore;
}