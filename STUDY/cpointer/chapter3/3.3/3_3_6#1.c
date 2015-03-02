//
// 関数ポインタ同士は等号や不等号で比較することができます。
// 
#include<stdio.h>

typedef int (*fptrOperation)(int, int);

int add(int num1, int num2){
	return num1 + num2;
}

int main(){

	fptrOperation fptr1 = add;

	// 以下の例では等号で比較をおこなっています。
	if(fptr1 == add){
		printf("fptr1 is add method\n");
	} else {
		printf("fptr1 isn't add method\n");
	}

	return 0;
}
