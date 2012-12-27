#include<iostream>
using namespace std;

class Hoge {
	public:
		Hoge(int n) : m_n(n)        { cout << "Hoge : " << m_n << endl; }
		Hoge(const Hoge&)           { cout << "Hoge& : " << m_n << endl; }
		void operator=(const Hoge&) { cout << "Hoge= : " << m_n << endl; }
		virtual ~Hoge()             { cout << "~Hoge :" << m_n << endl; }

	private:
		int m_n;
};

void Viss(int n){
	cout << n << endl;
}

int main(){
	Viss(0);
	Hoge hoge(1);
	Viss(1);
	hoge = Hoge(2);
	Viss(2);
}
