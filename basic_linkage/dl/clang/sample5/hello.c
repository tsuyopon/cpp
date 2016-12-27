#include <stdio.h>

// main.cに定義されている関数と同じ関数を定義する

extern void hoge() __attribute__((weak));

#ifdef SETHOGE
void hoge ()
{
    printf("I'm hoge in library\n");
}
#endif

int hello (int i)
{
	printf ("Library Hello, %d\n", i);
	if(hoge){
		hoge();
	} else {
		printf ("not implement hoge()\n");
	}
	return (i + 1);
}
