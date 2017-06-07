//  コンパイル
//  $ g++ sha.cc /lib64/libcrypto.so.10 -lssl -lcrypt
#include<iostream>
#include<openssl/sha.h>
#include<cstdio>
#include<cstring>

int main(){
	char rbuf[128];
	unsigned char wbuf[SHA_DIGEST_LENGTH];
	std::string str = "";
	while(fgets(rbuf, sizeof rbuf, stdin) ){
		if(strchr(rbuf, '\n')) *strchr(rbuf, '\n') = '\0';
		SHA1((unsigned char *)rbuf, strlen(rbuf), wbuf);
		printf("input: [%s], hash: [", rbuf);
		for(int i = 0; i < SHA_DIGEST_LENGTH; i++){
			printf("%02x",wbuf[i]);
		}
		printf("]\n");
		std::cout << std::endl;
		return 0;
	}
	return 0;
}
