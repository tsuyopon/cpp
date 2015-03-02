//
// int定数とint配列の初期化
//
#include<stdio.h>

int main(){
	int a1 = (const int){100};
	int *arr1 = (int[3]){10, 20, 30};
	int i;

	printf("a1=%d\n", a1);
	for(i=0; i<3; i++){
		printf("%d\n", arr1[i]);
	}
}
