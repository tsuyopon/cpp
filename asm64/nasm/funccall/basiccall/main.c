#include<stdio.h>

int func(int);

int main(int argc, char *argv[])
{
	int var;
	var = func(100);
	printf("answer = %d\n", var);
	return func(1);
}
