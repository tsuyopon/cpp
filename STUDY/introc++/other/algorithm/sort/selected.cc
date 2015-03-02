/*
 * 「選択ソート」アルゴリズムについては下記参照
 * http://www.geocities.jp/ky_webid/algorithm/003.html
 */
#include<stdio.h>
#define ARRAYSIZE 8

int main(void){
	int array[ARRAYSIZE] = {7, 14, 33, 10, 2, 19, 37, 20};
	int temp;

	for(int i = 0; i < ARRAYSIZE; i++){
		for(int j = i + 1; j < ARRAYSIZE; j++){
			if( array[i] < array[j] ){
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

	for(int i = 0; i < ARRAYSIZE; i++){
		printf("%d\t", array[i]);
	}
	printf("\n");
	return 0;

}
