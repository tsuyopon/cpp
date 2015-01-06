/*
 * 文字列の連結
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

	// 以下の２つの文字列を連結します。
	char* error = "ERROR: ";
	char* errorMessage = "Not enough money";

	// strcatの第１引数は結合した際の文字数を確保しなければなりません。
	char* buffer = (char*)malloc(strlen(error)+strlen(errorMessage)+1);

	// 最初に1つ目をstrcpyした後に、続いてconcatを実行することによって文字列を連結します。
	// WARNING: bufferを作らずにerrorにerrorMessageを直接追加しようとすると意図しない動作となります。
	strcpy(buffer, error);
	strcat(buffer, errorMessage);

	printf("buffer:       %s\n", buffer);
	printf("error:        %s\n", error);
	printf("errorMessage: %s\n", errorMessage);
}
