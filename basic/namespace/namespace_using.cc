#include<iostream>
using namespace std;

/*
 * usingについて(名前空間の可視化を行う)
 */

// usingよりも前にnamespace宣言が必要
namespace Azarashi {
	namespace Goma {
		void print(){
			cout << "Azarashi::Goma::print() START" << endl;
		}
	}
}

int main(){
	using namespace Azarashi::Goma;   // 名前空間の追加を行っています
	print();                          // Azarashi::Goma::print()として呼び出し不要であることに注目
	return 0;
}
