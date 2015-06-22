#include<iostream>
using namespace std;

class SingletonClass {
	private:
		SingletonClass(void) {}
		static SingletonClass* singleton;           // 変数がstaticで宣言されているのがポイント。なんど呼びだしても同じ位置をさしている
	public:
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


