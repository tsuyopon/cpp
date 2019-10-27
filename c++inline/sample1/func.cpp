#include "func.h"

int TestA::privateFunc(){
  return 123;
}

int TestA::getNumInCpp() {
  return 73 + getNumInH();
}
