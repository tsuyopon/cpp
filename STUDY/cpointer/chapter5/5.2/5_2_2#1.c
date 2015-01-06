#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	char name[32];
	char *names[30];
	size_t count = 0;

	printf("Enter your name: ");
	scanf("%s", name);

	// namesの先頭names[0]にmallocで入力された文字数+1個文の確保したアドレスを代入します。
	names[count] = (char*)malloc(strlen(name)+1);
	strcpy(names[count], name);
	printf("%s\n", names[count]);
}
