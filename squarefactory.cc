#include <iostream>
#include <sstream>
#include <string>
#include "squarefactory.h"
#include "settings.h"
#include "grid.h"

using namespace std;

SquareFactory* SquareFactory::instance = NULL;

SquareFactory::SquareFactory():settings(Settings::getInstance()),index(-1),productionCount(0){}

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


Square* SquareFactory::generateSquare(int r, int c, int level, string type){
  productionCount++;
  // generate square using probabilities here
  string color = getColor(r, c, level);
  type = (type.size()) ? type : getType(r, c, level);
  cerr << "generating square " << productionCount << " " << color << " " << type << endl;
  return createSquare(r, c, color, type, false);
}

Square* SquareFactory::generateIndependantSquare(int r, int c, int level, Grid& g, string type){
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
    return createSquare(r, c, pick(colors), (type.size()) ? type : getType(r, c, level), false);
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
  while(!invalids[colorSequence[(index++)%colorSequence.size()]]){
    // however, if we;ve checked everythikng, stop the loop and just return it
    if(index == start){
      break;
    }
  }
  string color = colorSequence[(index++)%colorSequence.size()];
  return createSquare(r, c, color, (type.size()) ? type : "basic", false);
  
}

// specifically create this square
Square* SquareFactory::createSquare(int r, int c, string color, string type, bool count){
  if(count){
    productionCount++;
  }
  if(type == "basic"){
    return new BasicSquare(r, c, color);
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
  // let x be the random number. 0 <= x <= 100
  double sum = 0;
  double random = rand() % 100;
  for(map<string, double>::iterator i = mapping.begin(); i != mapping.end(); i++){
    // if we are in the right range
    if(random <= sum+i->second*100 && random >= sum){
      return i->first;
    }
    sum += i->second*100;
  }
  cerr << "ERROR: " << random << endl;
  return "";
}

string SquareFactory::getColor(int r, int c, int level){
  if(index == -1){
    return pick(settings->getColorProbabilities(level));  
  }
  return colorSequence[(index++)%colorSequence.size()];
  
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
        i->second = 1/(probs.size()-1);
      }
    }
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
    colorSequence.push_back(settings->getColorFromEncoding(string(1, current)));
  }
}
