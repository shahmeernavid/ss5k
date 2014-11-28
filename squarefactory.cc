#include <iostream>
#include <sstream>
#include <string>
#include "squarefactory.h"
#include "settings.h"
#include "grid.h"

#include "squares/square.h"
#include "squares/basic.h"
#include "squares/lateral.h"
#include "squares/upright.h"
#include "squares/psychedelic.h"
#include "squares/unstable.h"


using namespace std;

SquareFactory* SquareFactory::instance = NULL;

SquareFactory::SquareFactory():settings(Settings::getInstance()),index(-1),productionCount(-1){}

SquareFactory::~SquareFactory(){}

SquareFactory* SquareFactory::getInstance(){
  if(!instance){
    instance = new SquareFactory();
    atexit(clean);
  }
  return instance;
}
void SquareFactory::clean(){
  delete instance;
}


Square* SquareFactory::generateSquare(int r, int c, int level, string type, bool count){
  // generate square using probabilities here
  string color = getColor(r, c, level);
  type = (type.size()) ? type : getType(r, c, level);
  // cerr << "generating square " << productionCount << " " << color << " " << type << endl;
  return createSquare(r, c, color, type, count);
}

Square* SquareFactory::generateIndependantSquare(int r, int c, int level, Grid& g, string type, bool count){
  map<string, double> colors = settings->getColorProbabilities(level);
  if(index == -1){
    int invalidCount = 0;
    for(map<string, double>::iterator i = colors.begin(); i != colors.end(); i++){
      if(g.match(r, c, i->first)){
        invalidCount++;
        double prob = i->second;
        i->second = 0;
        for(map<string, double>::iterator p = colors.begin(); p != colors.end(); p++){
          if(i->first != p->first){
            // distribute probability evenly
            p->second += prob/(colors.size()-invalidCount);
          }
        }
      }
    }
    // just default to red if we cant find any square
    if(invalidCount == colors.size()){
      return createSquare(r, c, "red", (type.size()) ? type : getType(r, c, level), count);
    }
    return createSquare(r, c, pick(colors), (type.size()) ? type : getType(r, c, level), count);
  }
  map<string, bool> invalids;
  for(map<string, double>::iterator i = colors.begin(); i != colors.end(); i++){
    if(g.match(r, c, i->first)){
      invalids[i->first] = true;
    }
  }
  // go through the sequence until we get a square that doesnt 
  // create a chain reaction
  int start = index;
  while(invalids[colorSequence[index%colorSequence.size()]]) {
    // cerr << colorSequence[index%colorSequence.size()] << endl;
    index++;
    // cerr << "in loop " << index << endl;
    // however, if we;ve checked everythikng, stop the loop and just return it
    if((index)%colorSequence.size() == (start)%colorSequence.size()){
      index = rand()%colorSequence.size();
      break;
    }
  }
  string color = colorSequence[(index)%colorSequence.size()];
  index++;
  string t = (type.size()) ? type : "basic"; 
  return createSquare(r, c, color, t, count);
  
}

// specifically create this square
Square* SquareFactory::createSquare(int r, int c, string color, string type, bool count){
  if(count){
    productionCount=(productionCount==-1) ? 1 : productionCount+1;
  }
  if(type == "basic"){
    return new BasicSquare(r, c, color);
  }
  else if(type == "lateral"){
    return new LateralSquare(r, c, color);
  }
  else if(type == "upright"){
    return new UprightSquare(r, c, color);
  }
  else if(type == "unstable"){
    return new UnstableSquare(r, c, color);
  }
  else if(type == "psychedelic"){
    return new PsychedelicSquare(r, c, color);
  }
  else{
    return NULL;
  }
}

// takes a pair<string, double> and inserts it into the given array
// n the correct order (ascending)
void SquareFactory::insert(vector<pair<string, double> >& array, pair<string, double> elem){
  for(int i = 0; i < array.size(); i++){
    if(elem > array[i]){
      array.insert(i+array.begin(), elem);
      return;
    }
  }
  array.push_back(elem);
}

// takes a mapping of keys to probabilities and produces a 
// value that corresponds to correct probability proportions
string SquareFactory::pick(map<string, double> mapping){
  // idea is to build a cdf
  // let x be the random number. 0 <= x < 100
  double sum = 0;
  double random = rand() % 100;
  for(map<string, double>::iterator i = mapping.begin(); i != mapping.end(); i++){
    // if we are in the right range
    if(random < sum+i->second*100 && random >= sum){
      return i->first;
    }
    sum += i->second*100;
  }
  cerr << "ERROR: " << random << " " << (mapping.begin())->first << endl;
  return "";
}

string SquareFactory::getColor(int r, int c, int level){
  if(index == -1){
    return pick(settings->getColorProbabilities(level));  
  }
  string color = colorSequence[(index)%colorSequence.size()];
  index++;
  return color;
  
}
string SquareFactory::getType(int r, int c, int level){
  map<string, double> probs = settings->getTypeProbabilities(level);
  // if production count is set, make probability of getting basic 0
  // while the probability of getting any other special square is even
  int specialCount = settings->getSpecialCount(level);
  if(productionCount % specialCount == 0 && specialCount != -1){
    for(map<string, double>::iterator i = probs.begin(); i != probs.end(); i++){
      if(i->first == "basic"){
        i->second = 0;
      }
      else{
        i->second += 1/(double)(probs.size()-1);
      }
    }
  }
  else if(specialCount != -1){
    return "basic";
  }
  return pick(probs);
}

void SquareFactory::reset(){
  productionCount = 0;
  index = 0;
  colorSequence = vector<string>();
}

void SquareFactory::setSequence(string seq){
  index = 0;
  stringstream stream(seq);
  char current;
  while(stream >> current){
    colorSequence.push_back(settings->getColorFromEncoding(current));
  }
}
