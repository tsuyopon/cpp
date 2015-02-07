#include<cstdio>

#define SOH 0x01   // ^A

int main(){
	char contchar[2];
	char contchar2 = 0x02;   // ^B
	contchar[0] = 1;         // ^A
	contchar[1] = 0x03;      // ^C
	printf("%c^n", contchar[0]);
	printf("%c^n", contchar[1]);
	printf("%c^n", contchar2);
	printf("%c^n", SOH);
	printf("\x04\n");        // ^D
	return 0;
}
