/*
 * strlen()簡易関数を作ってみる
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

size_t stringLength(char* string){
	size_t length = 0;
	while( *(string++) ) {
		length++;
	}
	return length;
}

int main(){

	char simpleArray[] = "simple string";
	char *simplePtr = (char*)malloc(strlen("simple string")+1);
	strcpy(simplePtr, "simple string");

	printf("%d\n", stringLength(simplePtr));
	printf("%d\n", stringLength(&simplePtr[0]));

	// この場合だと、char * であるsimpleArrayにアドレス演算子を付与しているので、&simpleArrayはcharへのポインタへのポインタとして、つまりchar **
	// として解釈されるので、互換性の無いポインタに対する警告が出力されます。
	printf("%d\n", stringLength(&simplePtr));

}


