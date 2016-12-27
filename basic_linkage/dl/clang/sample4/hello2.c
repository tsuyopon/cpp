#include <stdio.h>

int hello2 (int i)
{
	helloecho();  // 共有ライブラリhello.c中の関数を呼び出す
	return (i - 1);
}
