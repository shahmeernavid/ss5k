#include <string>
#include <map>
#include "level.h"
#include "level0.h"

using namespace std;

map<string, string> Level0::generateSquare(){
  map<string, string> output;
  output["color"] = "red";
  output["type"] = "basic";
  return output;
}