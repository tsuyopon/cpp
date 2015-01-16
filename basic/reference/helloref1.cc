#include <iostream>
using namespace std;

/*
 * 変数の別名としての機能である参照について
 */
int main(){
	int i = 100;
	int &ref = i;     // 参照の宣言ではアンパサンドを利用します。参照は必ず初期化が必要です。参照の配列も作れません。
	ref++;

	cout << i  << ":" << ref  << endl;   // iとrefの値は同じであることが確認できます。
	cout << &i << ":" << &ref << endl;   // iとrefのアドレスは同じであることが確認できます。
}
