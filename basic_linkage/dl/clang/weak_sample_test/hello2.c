#include <stdio.h>

__attribute__((weak)) void hello(void) {
    printf("Hello from weak\n");
}

int hello2 (int i)
{
	helloecho();  // 共有ライブラリhello.c中の関数を呼び出す
	return (i - 1);
}
