#include<iostream>
using namespace std;

/*
 * 関数のオーバーロード(ポリモーフィズム)
 * オブジェクトの初期化
 */

class MyClass{
	public:
		char *data;
		MyClass(char *);           // コンストラクタ(引数1つ)   ※関数のオーバーロード
		MyClass(bool, char *);     // コンストラクタ(引数2つ)
};


// 以下２つのコンストラクタは関数のオーバーロードです。これが成立するには、関数の型、または引数の数が異なることが条件です。
MyClass::MyClass(bool b, char *str){
	if(b){
		cout << str << endl;
	}
}

MyClass::MyClass(char *str){
	MyClass::data = str;
	cout << str << endl;
}

int main()
{

	// 引数が2つ以上の場合には、クラス名を省略することができません。
	cout << "######### PART1" << endl;
	MyClass o[3] = {
		MyClass(true,  "azarashi"),
		MyClass(false, "ashika"),
		MyClass(true,  "goma"),
	};

	// 引数が1つだけの場合には、クラス名を省略することができます。
	cout << "######### PART2" << endl;
	MyClass o2[3] = {
		"test1",
		"test2",
		"test3",
	};

	// オブジェクトのポインタにより操作します
	cout << "######### PART3" << endl;
	MyClass *o3;
	o3 = &o2[0];                               // o2の先頭アドレスをo3に格納しています。
	cout <<     o3->data << endl;              // o3を出力しています。
	cout << (o3+1)->data << endl;              // (o3+1)というアドレス演算によりo2[1]を出力制御していることに注意。"*"も付加されていません。
	cout << (o3+2)->data << endl;              // (o3+2)というアドレス演算によりo2[2]を制御していることに注意。"*"も付加されていません。

	return 0;
}
