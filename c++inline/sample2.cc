/*
 * クラス内で定義されたメンバー関数に対するインライン化の取り扱いについて
 *
 * 参考: http://wisdom.sakura.ne.jp/programming/cpp/cpp14.html
 */
#include <iostream>
using namespace std;

class Kitty {
public:
    // クラス内で定義したメンバ関数の場合にはinlineを直接指定しなくても自動的にインライン化が行われます。(inlineキーワードを指定してもよい)
	int func(int x) {
		return x + (int)(x * 0.05);
	}
} obj ;

int main() {
	cout << obj.func(100);
	return 0;
}
