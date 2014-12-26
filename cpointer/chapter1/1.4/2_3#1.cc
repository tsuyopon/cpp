#include<stdio.h>

int main(){

	// 以下をコメントインしてコンパイルすると下記エラーが表示されます。
	// これはcpi宣言にconst intの型を入れるのであれば、
	//    error: invalid conversion from 'const int*' to 'int*' [-fpermissive]
//	const int limit0 = 500;
//	int *const cpi0 = &limit0;

	const int limit = 100;

	/* 定数への定数ポインタの宣言 */
	// 以下の宣言によって「ポインタ値の変更」と「ポインタが指し示しているデータの変更」は出来ません。
	// つまり、下記はポインタ宣言すると同時に初期化しなければコンパイル時にエラーとなりますので注意が必要です。
	// この宣言が必要となる場面は非常に稀なことが多いようです。
	const int * const cpci = &limit;

	printf("cpci_addr=%d, cpci_value=%d, limit_value=%d\n", &cpci, *cpci, limit);

}
