#include<stdio.h>
#include<stdlib.h>

int add(int a, int b){ return a + b; }
int sub(int a, int b){ return a - b; }
int mul(int a, int b){ return a * b; }

int main(void){

	// 関数ポインタの配列(関数ポインタテーブルと呼ぶ)
	// 1. (*arithFuncTable[])と*が（）で囲まれているのは戻り値がintなので、int*にならないようにするため
	// 2. arithFunctable[]により配列を表しています。
	// 3. arithFuncTable[]にかかる*は値であることを意味しています。つまりarithFuncTable[1]などが関数名であるということを意味しているようです。
	// 4. 実は*とarithFuncTableの間にはconstを入れた方がいいかもしれません。(時間があれば試してみてください)
	//
	// これの利点としては switch ~ caseなどの処理をより単純にしてくれることができるようになります。
	int (* arithFuncTable[])(int, int) = {add, sub, mul};
	int i;

	for(i = 0; i < 3; i++){
		
		printf("%s\n", );
		printf("%d\n", arithFuncTable[i](10, 5));
	}
	return 0;
}
