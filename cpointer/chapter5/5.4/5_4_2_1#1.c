/*
 * 局所変数文字列のアドレスを関数から返す(使用してはならない)
 *   ##このプログラムは警告とともにコンパイルできますが、正しい挙動を示しません。
 */
#include<stdio.h>

#define MAX_TAB_LENGTH 32

char *blanks(int number){

	char spaces[MAX_TAB_LENGTH];
	int i;
	for(i = 0; i < number && i < MAX_TAB_LENGTH; i++){
		spaces[i] = ' ';
	}
	spaces[i] = '\0';

	// blanks関数内部で宣言した局所変数のアドレスを返すのは問題です。
	// なぜならば、この文字列は別の関数呼び出しによるスタックフレームによって上書きされる危険性があります。
	return spaces;
}

int main(){
	char *tmp;
	tmp = blanks(5);
	printf("#%s#\n", tmp);
}
