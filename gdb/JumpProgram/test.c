// gcc -g test.c
#include<stdio.h>

int main()
{

  static int test1 = 1;
  static int test2 = 0;
  static int test3 = 0;
  if( test1 == 1 || test2 == 0 || test3 == 0){
    printf("pattern 1\n");
  } else {
    printf("pattern 2\n");
  }
  printf("pattern 3\n");
}

