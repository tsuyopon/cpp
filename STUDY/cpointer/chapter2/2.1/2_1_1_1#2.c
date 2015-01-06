#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

	char *name = (char*)malloc(strlen("Susan")+1);
	strcpy(name, "Susan");
	while(*name != 0){
		printf("%c", *name);

		// 文字列のNUL終端文字を指した状態でループが終了します。
		// つまり、割り当てしたメモリの最初のアドレスは紛失してしまいました。
		name++;
	}

	// nameが先頭ポインタを指していないのでfreeを実行してもinvalid pointerエラーとなります。
	free(name);

}
