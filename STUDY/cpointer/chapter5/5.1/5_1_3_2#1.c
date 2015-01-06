//
// 文字列の初期化
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

	char *header1 = (char*)malloc(strlen("Media Player")+1);
	strcpy(header1, "Media Player");
	printf("header1=%s\n", header1);

	char *header2 = "Media Player";
	printf("header2=%s\n", header2);

}
