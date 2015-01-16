#include<iostream>
using namespace std;

/*
 * 名前空間の定義について
 */


// 名前空間は必ずグローバルな位置で定義を行うこと

// 名前空間位置の複数分割の例(分割していますが、共にMySpace名前空間として扱われます)
namespace MySpace {
	void MySpace();
}

namespace MySpace {
	void MySpace(){
		cout << "MySpace::MySpace() START" << endl;
	}
}


// 名前空間のネストの例
namespace Azarashi {
	namespace Goma {
		void print(){
			cout << "Azarashi::Goma::print() START" << endl;
		}
	}
}

// 無名名前空間の例
namespace {
	char *str = "MUMEI NAMESPACE START";  // 無名名前空間で定義される変数は他のファイルからアクセスすることはできません。(extern char *strによるアクセスも不可です)
}

// 名前空間に対するエイリアス設定
namespace que = Azarashi::Goma;

int main(){
	MySpace::MySpace();
	Azarashi::Goma::print();   // 名前空間のネスト呼び出し
	cout << ::str << endl;     // 無名名前空間呼び出し
	que::print();              // 名前空間エイリアスを利用した呼び出し
	return 0;
}
