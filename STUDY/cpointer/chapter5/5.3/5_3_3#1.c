/*
 * 関数に渡した文字列を初期化するプログラム(part1)
 */
#include<stdio.h>
#include<stdlib.h>

char* format(char *buffer, size_t size, const char* name, size_t quantity, size_t weight){
	snprintf(buffer, size, "Item: %s, Quantity: %u, Weight: %u", name, quantity, weight);
	return buffer;
}

int main(){

	// "char *buffer"の宣言だと領域が確保されないので、セグフォをおこします。
	// このため、十分な範囲を指定して確保しておく必要があります。
	char buffer[100];
	printf("%s\n", format(buffer, sizeof(buffer), "Axle", 25, 45));
}
