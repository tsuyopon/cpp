#include<iostream>
using namespace std;

/*
 *  関数のインライン化を行っています。
 *      ※ これによりオーバーヘッドを現象できます。inlineできるかどうかはコンパイラによる
 *  メンバー関数のインライン化を行っています。
 */

// メンバー関数のインライン化
class MyClass{
	public:
		int memberfunc(int x){
			return x * x;
		}
} obj;

// 関数のインライン化
inline int func(int x){
	return x * x;
}

int main(){
	// 関数のインライン化確認
	cout << func(10) << endl;

	// メンバー関数のインライン化確認
	cout << obj.memberfunc(20) << endl;

	return 0;
}

