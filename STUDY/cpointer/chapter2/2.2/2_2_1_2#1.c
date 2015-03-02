#include<stdio.h>
#include<stdlib.h>

int main(){
	int *pi;

	// メモリへの割当処理を行わずにdumpしようとするとセグフォを起こします。
	printf("%d\n", *pi);
}
