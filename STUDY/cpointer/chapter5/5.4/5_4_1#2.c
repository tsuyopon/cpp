/*
 * 関数から文字列定数を返す
 */
#include<stdio.h>

char* returnALiteral(int code, int subCode){
	static char* bpCenter = "Boston Processing Center";
	static char* dpCenter = "Denver Processing Center";
	static char* apCenter = "Atlanta Processing Center";
	static char* sjpCenter = "San Jose Processing Center";

	switch(code){
		case 100:
			return bpCenter;
		case 135:
			if(subCode < 35){
				return dpCenter;
			} else {
				return bpCenter;
			}
		case 200:
			return dpCenter;
		case 300:
			return apCenter;
		case 400:
			return sjpCenter;
	}
}

int main(){
	printf("%s\n", returnALiteral(135, 35));
}
