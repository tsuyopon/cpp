// g++ -g test.cc
#include <stdio.h> 

int abs(int x)
{
  return( (x < 0) ? -x : x );
}

int abs(int x, int y)
{
  return x;
}

long abs(long x)
{
   return( (x < 0L) ? -x : x);
}

double abs(double x)
{
   return( (x < 0.0) ? -x : x);
}

int main(void)
{
   printf("%d \n", abs(-8));
   printf("%d \n", abs(1, 2));
   printf("%ld \n", abs(14L));
   printf("%f \n", abs(-33.5));
   return 0;
}
