#include <stdio.h>

char s1[] = "s1 is array";
char *s2  = "s2 is pointer";

int main(){
	printf(" s1     = 0x%08x\n", (unsigned int)s1);
	printf("&s1     = 0x%08x\n", (unsigned int)&s1);
	printf("&s1[0]  = 0x%08x\n", (unsigned int)&s1[0]);
	printf("&s1[1]  = 0x%08x\n", (unsigned int)&s1[1]);
	printf(" s2     = 0x%08x\n", (unsigned int)s2);        // ポインタが指し示す値を表示する
	printf("&s2     = 0x%08x\n", (unsigned int)&s2);       // ポインタのアドレスを表示する
	printf("&s2[0]  = 0x%08x\n", (unsigned int)&s2[0]);
	printf("&s2[1]  = 0x%08x\n", (unsigned int)&s2[1]);
	printf("siteof(s1) = %d\n", sizeof(s1));
	printf("siteof(s2) = %d\n", sizeof(s2));
	exit(0);
}
