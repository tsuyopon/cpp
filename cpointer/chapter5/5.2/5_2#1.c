#include<stdio.h>

int main(){
	char command[16];
	printf("Enter a Command: ");
	scanf("%s", command);
	if(strcmp(command, "Quit") == 0){
		printf("The command was Quit\n");
	} else {
		printf("The command was not Quit\n");
	}
	return 0;
}
