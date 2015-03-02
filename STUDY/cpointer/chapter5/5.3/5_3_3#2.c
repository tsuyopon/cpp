/*
 * 関数に渡した文字列を初期化するプログラム(part2)
 *   
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* format(char *buffer, size_t size, const char* name, size_t quantity, size_t weight){

	char *formatString = "Item: %s, Quantity: %u, Weight: %u";
	size_t formatStringLength = strlen(formatString)-6;  // -6は%s, %s, %uの6文字分を表します。
	size_t nameLength = strlen(name);
	size_t length = formatStringLength + nameLength + 10 + 10 + 1;  // 10 + 10: 数値と重さをフォーマットする際の予想される最大長、+1: NULL

	if( buffer == NULL ){
		buffer = (char*)malloc(length);
		size = length;
	}

	snprintf(buffer, size, formatString, name, quantity, weight);
	return buffer;
}

int main(){

	// 5_3_3#1.cでは char buffer[100];と定義していたがここではポインタ宣言しかしていないことに注意
	char *buffer;
	printf("%s\n", format(buffer, sizeof(buffer), "Axle", 25, 45));
	free(buffer);

}
