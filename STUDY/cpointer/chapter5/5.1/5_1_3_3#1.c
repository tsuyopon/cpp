#include<stdio.h>

int main(){
	char *command;
	printf("Enter a Command: ");
	scanf("%s", &command);
	printf("Your input: %s\n", command);
	// commandのための領域が割り当てられていないので実行するとセグフォとなります。
}
