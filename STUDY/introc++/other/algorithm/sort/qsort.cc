/*
 *  qsortを利用して関数ポインタについて学習する
 *
 */
#include<stdio.h>
#include<stdlib.h>

// 以下では「void *a」となっていますが、void型ポインタはどんなポインタでも受け入れることが
// できるようになっています。
// (参考) http://www.mm2d.net/c/c-17.shtml
//        http://www.cc.kyoto-su.ac.jp/~yamada/ap/qsort.html
int compare(const void *a, const void *b){
	/* 「*(int*)a」という記述は
	 *  (int*)aによってaをint型のアドレスにキャストしています。
	 *  *(int*)aによって上記で取得したアドレスを値に変換していることになります。
	 */
	return *(int *)a - *(int *)b;

	// 戻り値に関する注意点
	// aの値がbの値よりも先であれば負を返し、逆であれば正を返します。
	// aの値とbの値のどちらが先でもいいときには0を返しています。
}

int main(void){
	int array[10] = { 27, 10, 7, 8, 9, 12, 22, 14, 13, 3};
	int i;

	/*
	 * void qsort(void *base, size_t n, size_t size, int (*fnc)(const void*, const void*))
	 *
	 * ここで  int (*fnc)(const void*, const void*)
	 * という記述は
	 * *fncは値であることを示しています。この値は関数名称で、ここでいうcompareです。
	 * void*はどんなポインタでも受け入れることが可能であることを表し、constが付与されることによって、
	 * 内部的に値が変更されることがないことを意味しています。
	 */
	qsort(array, 10,  sizeof(int), compare);     // compareとして関数ポインタが指定されている。要するにコールバック関数です。
	for(i = 0; i < 10; i++){
		printf("%d,", array[i]);
	}
	printf("\n");
	return 0;
}
