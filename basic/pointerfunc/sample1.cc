/*
 * 関数ポインタ利用サンプル
 *
 * 参考: http://www.nurs.or.jp/~sug/soft/tora/tora13.htm
 */

#include<stdio.h>

int add(int a, int b){
	return a+b;
}

int sub(int a, int b){
	return a-b;
}

int main(){
	int (*func[2])(int, int);   // 関数ポインタ配列の宣言
	int x, y;
	int input;

	// 関数登録
	func[0] = add;
	func[1] = sub;

	// 代入
	x = 10;
	y = 9;

	printf("execute add type 0. execute sub type 1 > ");
	scanf("%d", &input);
	if(input == 0){
		printf("add result = %d\n", (*func[input])(x,y));
	} else if(input == 1){
		printf("sub result = %d\n", (*func[input])(x,y));
	} else {
		printf("set 1 or 0\n");
	}
	return 0;
}
