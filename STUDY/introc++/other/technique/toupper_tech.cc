#include<stdio.h>
#include<ctype.h>  // for toupper()

int main(void){
	int i = 0;
	char s[] = "helloooooo";

	while( s[i] != '\0' ){
		s[i] = s[i] - 32;   // 「s[i] = touppper(s[i]);」と同じ。32引くことでASCIIは大文字になることを利用しています。
		i++;
	}

	printf("%s\n", s);
	return 0;
}
