#include<iostream>
using namespace std;

/*
 * フレンド関数の使用法について(複数クラスでの取り扱い)
 */

class Age;

class Name {
		char *name;
	public:
		friend void print(Name &, Age &);    // (1): (2)と全く同じ構文で、friend関数宣言であることに注意

		// コンストラクタ
		Name(char *name){
			Name::name = name;
		}

} n_obj("Azarashi");

class Age {
		int age;
	public:
		friend void print(Name &, Age &);    // (2): (1)と全く同じ構文で、friend関数宣言であることに注意

		// コンストラクタ
		Age(int age){
			Age::age = age;
		}

} a_obj(3);

// メンバー関数の実体
void print(Name &n, Age &a){
	cout << "Name:" << n.name << "\tAge:" << a.age << endl;
}

int main(){
	print(n_obj, a_obj);                    // フレンド関数を呼び出しています
	return 0;
}
