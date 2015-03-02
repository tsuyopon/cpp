#include<stdio.h>
#include<stdlib.h>

int main(){

	// chunk変数にヒープからメモリを割り当てるプログラムです。freeしていいないのでずっと実行するとメモリリークで異常終了します。
	char *chunk;
	while(1){
		chunk = (char*)malloc(100000000);
		printf("Allocating\n");
	}
}
