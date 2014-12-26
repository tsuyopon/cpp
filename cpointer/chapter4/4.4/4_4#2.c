//
// mallocで割り当てた領域をtrimして、callocで領域を縮小します。
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *trim(char* phrase){
	char *old = phrase;
	char *new = phrase;

	// スペースがある間はoldの先頭ポジションを増加させたいので、oldポインタを1つ増加させる
	while(*old == ' '){
		old++;
	}

	// oldの値が存在していれば、while文を実行する。
	// oldではポインタのポジションからスペースを除去して"cat"の先頭にあたるようになっている。
	// mallocの領域を再利用したままc, a, tの順番でnewポインタの先頭から順番にoldの値をコピーしていっています。
	while(*old){
		// oldにアドレスを1追加した値を、newにアドレス1追加した値に代入している
		// つまり、oldの最初の2つのスペースはポジション移動をしているので、oldの3番目の"c"はnewの1番目、oldの4番目の"a"はnewの2番目、oldの5番目の"t"はnewの３番目となります。
		*(new++) = *(old++);
	}

	// これを付与しないと"catat"みたいな値で表示されてしまう。
	*new = 0;  // '\0'でもOK

	return (char*)realloc(phrase, strlen(phrase)+1);
}

int main(){
	char *buffer = (char*)malloc(strlen("  cat") + 1);
	strcpy(buffer, "  cat");
	printf("%s\n", trim(buffer));
}
