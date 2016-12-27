#include <stdio.h>

int hello (int i)
{
	printf ("Library Hello, %d\n", i);
	mainhoge();    // call mainhoge in main.c
	return (i + 1);
}
