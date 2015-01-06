#include <iostream>
using namespace std;

class Hoge {
	public:
		Hoge(int* cp);
};

Hoge::Hoge(int* cp){
	int* p = cp;
	cout << *p << endl;
}

int main(){
	int a = 5;
	const int* p = &a;
	Hoge(const_cast<int*>(p));  // compile ok

//	Hoge((int*)p);              // compile ok
//	Hoge((const int*)p);        // compile error
//	Hoge(p);                    // compile error
}
