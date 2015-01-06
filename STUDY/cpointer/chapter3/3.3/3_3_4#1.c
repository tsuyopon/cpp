//
// 関数ポインタを返す関数について学習します。
// 
#include<stdio.h>

typedef int (*fptrOperation)(int, int);

int add(int num1, int num2){
	return num1 + num2;
}

int sub(int num1, int num2){
	return num1 - num2;
}

// 以下の関数は関数ポインタを返しています。
fptrOperation select(char opcode){
	switch(opcode){
		case '+': return add;
		case '-': return sub;
	}
}

int evaluate(char opcode, int num1, int num2){
	fptrOperation operation = select(opcode);
	return operation(num1, num2);
}

int main(){
	printf("%d\n", evaluate('+', 5, 6));
	printf("%d\n", evaluate('-', 5, 6));
	return 0;
}
