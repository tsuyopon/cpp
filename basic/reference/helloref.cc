/*
 * 参照を返す関数・参照引数を渡す関数・参照オブジェクトの宣言を使ったサンプルプログラム
 * http://homepage2.nifty.com/assua/aosite/cpp/cpp_intro/cpb18.html
 */

#include<iostream>
using namespace std;

int &ref(){
	//cout << "called &ref()" << endl;
	static int x = 123;  // ローカル変数の参照を指し示す場合には、変数が消滅しないようにstaticを利用します。
	return x;
}

// 参照引数を渡す関数
int ref(int& n){
	//cout << "called ref(int& n)" << endl;
	n++;
	return n;
}

int main(){
	int j;
	int i = 100;
	cout << ++ref() << endl;
	cout << ++ref() << endl;
	cout << ++ref() << endl;

	ref() = 15; // 左辺に使う
	cout << --ref() << endl;
	cout << --ref() << endl;
	cout << --ref() << endl;

	j = ref(i); // 右辺に使う
	cout << j << endl;

	int& refobj = j;   // 参照オブジェクトの宣言
	cout << refobj << endl;

	//参照オブジェクトには値を直接代入することができるが、別の参照先にするようなことはできません。
	refobj = 999;
	cout << "refobj=" << refobj << ", j=" << j << endl;
	return 0;
}
