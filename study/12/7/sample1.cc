/*
 * 単純に値を返すだけの関数などは、呼ぶ回数が多いとそれだけ関数を呼び出すオーバーヘッドが大きくなる。
 * このためにインライン関数という仕組みを使うと処理をその場所に埋め込んでくれることができる。
 */
#include <iostream>
using namespace std;

class Test{
	public:
		Test(int i);
		int Get();
		int var;
};

Test::Test(int i){
	var = i;
}

int Test::Get(){
	return var;
}


int main(){
	Test test(3);
	for(double i=0; i < 500000000; i++){
		test.Get();
	}
	cout << "End of Program." << test.Get() << endl;
}
