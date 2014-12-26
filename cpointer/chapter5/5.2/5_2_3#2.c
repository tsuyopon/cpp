/*
 * 文字列の連結(5_2_3#1.cと異なりbufferを作らない方法)
 *   この方法だとバグがあります。
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

	// 以下の２つの文字列を連結します。
	char* error = "ERROR: ";
	char* errorMessage = "Not enough money";

	strcat(error, errorMessage);

//	printf("error:        %s\n", error);
//	printf("errorMessage: %s\n", errorMessage);
}
