#include<stdio.h>
#include<stdlib.h>

int main(){

//  charポインタを初期化するのに、文字定数を使うのは正しくありません。
//  文字定数の型はintであるため、charへのポインタにintを代入することになるので以下の場合にはプログラムは異常終了します。
//	char* prefix = '+';
//	printf("%s\n", prefix);

	// 以下にmalloc関数を利用した正しい手法を紹介致します。
	char *prefix = (char*)malloc(2);
	*prefix = '+';
	*(prefix+1) = 0;
	printf("%s\n", prefix);

}
