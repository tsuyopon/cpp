// $ gcc -g -O0 test.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
* Returns 0 on success, and
* Returns 1 on failure
*/
int authenticate (char *test)
{
  if(strcmp(test,"PASS") == 0 ) {
	  return 0; /* success*/
  } else {
      return 1; /* fail */
  }
}

/* USAGE: . /a.out FAIL */
int main(int argc, char *argv[])
{
  int retVal = -1;
  if (argc< 2)
  {
    printf ("\n USAGE: %s <PASS|FAIL>\n", argv[0]);
    exit (-2);
  }
  /* skipping any checks on argv to keep it simple*/
  retVal = authenticate(argv[1]);
  /* WE WILL USE GDB TO ALTER RETURN VALUE OF THIS CALL JUST BEFORE
  COPYING THE RETURN VALUE TO VARIABLE retVal */
  if( retVal == 0)
  printf("Authenticated ...program continuing...\n");
  else
  {
    printf("Wrong Input, exiting...\n");
    exit (retVal);
  }
}
