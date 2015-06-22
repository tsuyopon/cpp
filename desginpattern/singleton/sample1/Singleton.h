#include<iostream>
using namespace std;

class SingletonClass {
	private:
		// ポイント1: コンストラクタをprivateにする。コピーコンストラクタをprivateにする。
		SingletonClass(void) {}
		// ポイント2: privateでstaticな自分自身のポインタ型をメンバ変数に追加する。
		static SingletonClass* singleton;
	public:
		// ポイント3: publicでstaticな自分自身へのポインタを返す関数をメンバ関数に追加する。
		static SingletonClass* getInstance(void) {  // 
			return singleton;
		}
		void start(void);
		bool doSomething(int something);
		bool end(void);
};

SingletonClass* SingletonClass::singleton = new SingletonClass();

inline void SingletonClass::start(void)
{
	cout << "start" << endl;
	return;
}

inline bool SingletonClass::doSomething(int something)
{
	cout << "doSomething param:" << something << endl;
	return true;
}

inline bool SingletonClass::end(void)
{
	cout << "end" << endl;
	return true;
}


