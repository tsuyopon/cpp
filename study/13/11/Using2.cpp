#include <iostream>

namespace Hoge {
	using namespace std;

	void Hello() {
		cout << "Hi, Hello" << endl;
	}
}

int main(){
	Hoge::Hello();
}
