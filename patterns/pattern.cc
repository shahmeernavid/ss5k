#include "pattern.h"

Pattern::Pattern(int p):priority(p){}

Pattern::~Pattern(){}

int Pattern::getPriority(){
  return priority;
}