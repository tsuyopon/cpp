/*
 * 単純に値を返すだけの関数などは、呼ぶ回数が多いとそれだけ関数を呼び出すオーバーヘッドが大きくなる。
 * このためにインライン関数という仕組みを使うと処理をその場所に埋め込んでくれることができる。
 */
#include <iostream>
using namespace std;

inline int Get(){
	return 100 * 100 * 100;
}

int main(){
	for(double i=0; i < 500000000; i++){
		Get();
	}
	cout << "End of Program." << Get() << endl;
}
