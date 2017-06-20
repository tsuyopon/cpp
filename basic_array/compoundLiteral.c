// コンパウンドリテラルとは、無名変数を記述する方法で、C99での拡張仕様。 gccでコンパイル可能
// C++には入っていない気がする
// https://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html
#include<stdio.h>

void main(){

	// 1次元
	int *p = (int[]){1, 2, 3, 4};

	// ジャグ配列
	int (*(arr[])) = {
		(int[]){0, 1, 2, 3},
		(int[]){4, 5},
		(int[]){6, 7, 8}
	};

	// 文字配列
	char **foo = (char *[]) { "x", "y", "z" };
}
