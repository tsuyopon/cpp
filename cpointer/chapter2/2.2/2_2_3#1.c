#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	char *string1;
	char *string2;
	char *string3;
	char *string4;
	string1 = (char*)malloc(16);
	strcpy(string1, "0123456789AB");

	string2 = realloc(string1, 8);
	string3 = realloc(string1, 4);
	string4 = realloc(string1, 64);
	printf("string1 value: %p [%s]\n", string1, string1);
	printf("string2 value: %p [%s]\n", string2, string2);
	printf("string3 value: %p [%s]\n", string3, string3);
	printf("string4 value: %p [%s]\n", string4, string4);

}
