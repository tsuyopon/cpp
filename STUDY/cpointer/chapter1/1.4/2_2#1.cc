#include<stdio.h>

int main(){

	// 以下の３行をコメントインする前とした後双方でコンパイルをして実行結果を比較してみると。num3の初期化の値が異なる
	// つまり、この値は初期化しないと信用できないということか???

//	int num1;
//	int *const cpi1 = &num1;
//	printf("cpi1, num1: addr=%p, value=%d\n", cpi1, num1);

    // 「*」は間接演算子と呼ばれます。
	int num2 = 0;
	int *const cpi2 = &num2;
	printf("cpi2, num2: addr=%p, value=%d\n", cpi2, num2);

    // このようにcpi3を初期化するとnum3も初期化されます
	int num3;
	int *const cpi3 = &num3;
	printf("cpi3, num3: addr=%p, value=%d\n", cpi3, num3);

}
