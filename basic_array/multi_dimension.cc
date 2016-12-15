/*
 * char *data[N]とchar*[N][100]などの宣言によるメモリ領域の使い方の差異を見るためのサンプルプログラム
 */
#include<iostream>

using namespace std;

void sub(const char* const *in, int n){
	for(int i = 0; i < n; i++){
		cout << in[i] << endl;
	}
}

void sub2(const char in[][100], int n){
	for(int i = 0; i < n; i++){
		cout << in[i] << endl;
	}
}

int main(){

	{
		char *data[2] = {(char*)"abcdefg", (char*)"hijklmn"};
		cout << (void*)&data[0] << ":" << (void*)&data[1] << " : sum of address &[1] - &[0] :" << ( (long)&data[1] - (long)&data[0]) << endl;
		sub(data, 2);
	}

	{
		char data[2][100] = {"abcdefg", "hijklmn"};
		cout << (void*)&data[0] << ":" << (void*)&data[1] << " : sum of address &[1] - &[0] :" << ( (long)&data[1] - (long)&data[0]) << endl;
		sub2(data, 2);
	}
}
