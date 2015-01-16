#include<iostream>
using namespace std;

/*
 *  関数のオーバーロードについて(ポリモーフィズム)
 */

class MyClass {
	public:
		// コンストラクタのオーバーロード
		MyClass(){
			cout << "no args" << endl;
		}
		MyClass(char *str){
			cout << str << endl;
		}
		
		// 一般関数のオーバーロード
		void Azarashi(){
			cout << "Azarashi: kyu-" << endl;
		}
		void Azarashi(char *str){
			cout << "Azarashi: " << str << endl;
		}

		// (注意) デストラクタについてはオーバーロードを利用することは出来ません。
} obj;

int main()
{
	obj = MyClass("testtest");
	obj.Azarashi();
	obj.Azarashi("kyu-kyu-");
	return 0;
}
