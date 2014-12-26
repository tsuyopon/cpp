#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int compare(const char* s1, const char* s2);
int compareIgnoreCase(const char* s1, const char* s2);
char* stringToLower(const char* string);

int compare(const char* s1, const char* s2){
	return strcmp(s1, s2);
}

int compareIgnoreCase(const char* s1, const char* s2){
	char* t1 = stringToLower(s1);
	char* t2 = stringToLower(s2);
	int result = strcmp(t1, t2);
	free(t1);
	free(t2);
	return result;
}

char* stringToLower(const char* string){
	char *tmp = (char*)malloc(strlen(string)+1);
	char *start = tmp;
	while( *string != 0 ){
		*tmp++ = tolower(*string++);
	}
	*tmp = 0;
	return start;
}

int main(){
	const char *str1 = "TsUyOsHi";
	const char *str2 = "tSuYoShI";

	int ret = compare(str1, str2);
	printf("compare: %d\n", ret);

	int ret2 = compareIgnoreCase(str1, str2);
	printf("compareIgnoreCase: %d\n", ret2);
}

