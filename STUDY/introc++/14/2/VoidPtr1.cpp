#include<iostream>
using namespace std;

int main(){
	char   c = '1';
	int    i = 2;
	double d = 3;
	void* p;         // void型へのポインタ宣言

	p = &c;
	cout << *static_cast<char*>(p) << ' ';   // void型ポインタはキャストすることによって問題無く参照先へとアクセスできます。

	p = &i;
	cout << *static_cast<int*>(p) << ' ';

	p = &d;
	cout << *static_cast<double*>(p) << endl;
}
