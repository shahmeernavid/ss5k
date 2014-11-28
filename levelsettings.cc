#include "levelsettings.h"
#include <iostream>

using namespace std;

LevelSettings::LevelSettings():levelUpScore(0),specialCount(-1),lockedCellsPercent(0),patterns(vector<Pattern*>(0)), inputFile("") {
}

LevelSettings::~LevelSettings(){
  for(int i =0; i < patterns.size(); i++){
    delete patterns[i];
  }
}

void LevelSettings::addType(string name, double prob){
  cerr << "adding type: " << name << " " << prob << endl;
  types.push_back(name);
  typeProbabilities[name] = prob;
}
void LevelSettings::addColor(string name, double prob){
  colors.push_back(name);
  colorProbabilities[name] = prob;
}

// accessor methods
double LevelSettings::getColorProbability(string name) const{
  return colorProbabilities.at(name);
}
double LevelSettings::getTypeProbability(string name) const{
  return typeProbabilities.at(name);
}
map<string, double> LevelSettings::getColorProbabilities() const{
  return colorProbabilities;
}
map<string, double> LevelSettings::getTypeProbabilities() const{
  return typeProbabilities;
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

void LevelSettings::setSpecialCount(int c){
  specialCount = c;
}
int LevelSettings::getSpecialCount() const{
  return specialCount;
}

void LevelSettings::setLockedCellsPercent(double p){
  lockedCellsPercent = p;
}
double LevelSettings::getLockedCellsPercent() const{
  return lockedCellsPercent;
}

void LevelSettings::setInputFile(string name){
  inputFile = name;
}
string LevelSettings::getInputFile(){
  return inputFile;
}