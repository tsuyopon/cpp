// $ gcc -g -O0 test.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* USAGE: . /a.out FAIL */
int main(int argc, char *argv[])
{
  int retVal = -1;
  if (argc< 2)
  {
    printf ("\n USAGE: %s <PASS|FAIL>\n", argv[0]);
    exit (-2);
  }

  /* WE WILL USE GDB TO ALTER RETURN VALUE OF THIS CALL JUST BEFORE
  COPYING THE RETURN VALUE TO VARIABLE retVal */
  if( strcmp(argv[1], "PASS") == 0)
  printf("Authenticated ...program continuing...\n");
  else
  {
    printf("Wrong Input, exiting...\n");
    exit (retVal);
  }
}
