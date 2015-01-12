/*
 *
 */
#include<iostream>
using namespace std;

// <class T>はCSampleクラス内部でテンプレートを使いますよということを意味している
template <class T> class CSample
{
	public:
		CSample(T t) : m_value(t){}
		// func定義
		// <class U>はfuncメソッド内部で使用する関数を表している
		template <class U> void func(const U& u){
			std::cout << m_value << std::endl;
			std::cout << u << std::endl;
		}
	private:
		T m_value;
};

int main(){
	cout << "START" << endl;
	CSample<int> obj(999);

	cout << "call func arg=aaa" << endl;
	obj.func("aaa");

	cout << "call func arg=2.34" << endl;
	obj.func(2.34);

	cout << "call func arg=100" << endl;
	obj.func(100);

	return 0;
}
