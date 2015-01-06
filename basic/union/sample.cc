/*
 *  REF: http://itpro.nikkeibp.co.jp/article/COLUMN/20071024/285445/
 */
#include<stdio.h>
#include<arpa/inet.h>

union ipv4 {
	// 192.168.1.23を入れると以下のようになります。
	unsigned char c[4];    // c[0]=192, c[1]=168, c[2]=1, c[3]=23
	unsigned short s[2];   // s[0]=C0A8, s[1]=0117
	unsigned int i;        // i=C0A80117
};

int main(){
	union ipv4 addr;
	int i;

	// IPアドレスをセットする
	addr.c[0]=192;
	addr.c[1]=168;
	addr.c[2]=1;
	addr.c[3]=23;

	// IPアドレスを表示する
	for(i=0; i<4; i++){ printf("%d.", addr.c[i]); }
	printf("\n");

	printf("%04X:%04X\n", addr.s[0], addr.s[1]);
	printf("%04X:%04X\n", htons(addr.s[0]), htons(addr.s[1]));

	printf("%X\n", addr.i);
	printf("%X\n", htonl(addr.i));
}
