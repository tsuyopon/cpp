#include <stdio.h>

int foo(int x, int y) {
  return x + y;
}

int bar(int x, int y) {
  return x - y;
}

int main(void) {
  printf("%d\n", foo(2, 3));
  printf("%d\n", foo(3, 4));
  return 0;
}
