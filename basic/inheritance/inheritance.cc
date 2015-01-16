#include<iostream>
using namespace std;

/*
 *  継承の仕組みについて
 */

class Azarashi {
	public:
		void cry(){
			cout << "Kyu-" << endl;
		}
		void gorogoro(){
			cout << "Gorogoro" << endl;
		}
};

class Goma : public Azarashi {
	public:
		void cry(){
			cout << "Kyu-Kyu-" << endl;
		}
		void hungry(){
			cout << "I want to eat fish" << endl;
		}
} obj;

int main()
{
	obj.gorogoro();          // Azarashiクラスのgorogor()が呼び出されます
	obj.hungry();            // Gomaクラスのhugry()が呼び出されます
	obj.Azarashi::cry();     // cry()はAzarashiとGoma双方のクラスにあるので、親クラスではスコープを利用して呼び出します。
	obj.cry();               // Gomaクラスのcry()が呼び出されます

	return 0;
}

