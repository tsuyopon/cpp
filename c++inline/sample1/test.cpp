#include "stdio.h"
#include "func.h"

int main(){
  TestA test;
  int a = test.getNumInCpp();
  int b = test.getNumInH();
  int c = test.getNumInline();
  int d = test.getNumCallCpp();
  printf("%d %d %d %d\n", a, b, c, d);

  return 0;
}
