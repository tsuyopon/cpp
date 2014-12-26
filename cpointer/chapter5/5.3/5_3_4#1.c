/*
 * コマンドライン上から引数を取得するプログラム
 */
#include<stdio.h>

// char **argvはchar *argv[]と等価です。
int main(int argc, char** argv){
	int i;
	for(i=0; i<argc; i++){
		printf("argv[%d] %s\n", i, argv[i]);
	}
}
