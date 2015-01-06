/*
 * 関数から文字列定数を返す
 */
#include<stdio.h>

char* returnALiteral(int code){
	switch(code){
		case 100:
			return "Boston Processing Center";
		case 200:
			return "Denver Processing Center";
		case 300:
			return "Atlanta Processing Center";
		case 400:
			return "San Jose Processing Center";
	}
}

int main(){
	printf("%s\n", returnALiteral(200));
}
