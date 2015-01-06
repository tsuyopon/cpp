//
// 関数ポインタを格納する配列を利用する
// 
#include<stdio.h>

typedef int (*fptrOperation)(int, int);
typedef int (*operation)(int, int);

// 関数ポインタを格納する配列を定義しています。この配列は同時にNULLに初期化されます。
operation operations[128] = {NULL};

// 上記typedefを使わない方法で宣言すると以下のようにします。
//int (*operations[128])(int, int) = {NULL};

int add(int num1, int num2){
	return num1 + num2;
}

int sub(int num1, int num2){
	return num1 - num2;
}

void initializeOperationsArray(){
	// 関数ポインタを配列に格納しています。
	operations['+'] = add;
	operations['-'] = sub;
}

int evaluateArray(char opcode, int num1, int num2){
	fptrOperation operation;
	operation = operations[opcode];
	return operation(num1, num2);
}

int main(){
	initializeOperationsArray();
	printf("%d\n", evaluateArray('+', 5, 6));
	printf("%d\n", evaluateArray('-', 5, 6));
	return 0;
}
