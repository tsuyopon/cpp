/*
 * 動的に割り当てたメモリを関数から返す場合
 */
#include<stdio.h>
#include<stdlib.h>

// 指定された文字数分のスペースを埋めて配列を返す関数
char *blanks(int number){
	char* spaces = (char*)malloc(number + 1);
	int i;
	for(i = 0; i < number; i++){
		spaces[i] = ' ';
	}
	spaces[number] = '\0';
	return spaces;
}

int main(){
	char *tmp = blanks(5);
	printf("#%s#\n", tmp);
	free(tmp);
}
