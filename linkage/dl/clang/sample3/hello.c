#include <stdio.h>

// main.cに定義されている関数と同じ関数を定義する
void hoge ()
{
    printf("I'm hoge in library\n");
}

int hello (int i)
{
	printf ("Library Hello, %d\n", i);
	hoge();
	return (i + 1);
}
