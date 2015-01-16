#include<iostream>
using namespace std;

/*
 *  「::」スコープ演算子を利用したクラスメソッド登録
 *  コンストラクタ登録方法
 *  デストラクタ登録方法
 */

class MyClass {
	private:
		int point;
	public:
		MyClass();                         // コンストラクタ メンバー
		~MyClass();                        // デストラクタ   メンバー
		void setPoint(int i);
		int  getPoint(int i);
};

MyClass::MyClass(){                        // コンストラクタ
	cout << "START PROGRAM" << endl;
}

MyClass::~MyClass(){                       // デストラクタ(引数を渡すことはできません)
	cout << "END PROGRAM" << endl;
}

void MyClass::setPoint(int i){             // 「::」スコープ解決演算子
	point = i;
}

int MyClass::getPoint(int i){
	point += 1;
	return point;
}

int main()
{
	MyClass obj;
	obj.setPoint(1);
	for(int i = 0; i < 10; i++){
		cout << obj.getPoint(i) << endl;
	}
	return 0;
}


