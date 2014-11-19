#include "level0.h"

using namespace std;

Level0::Level0(){

}


map<string, string> Level0::generateSquare(){
  map<string, string> output;
  output["color"] = "red";
  output["type"] = "basic";
  return output;
}