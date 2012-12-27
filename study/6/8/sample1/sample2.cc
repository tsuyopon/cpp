/*
 * Copy Constructor sample program.
 */
#include<iostream>
using namespace std;

class Test {
	public:
		Test();
		~Test();
		int *m_array;
};

Test::Test(){
	m_array = new int[5];
	cout << "Constructor." << endl;
}

Test::~Test(){
	cout << "Destructor." << endl;
	delete [] m_array;
}

void Func1(const Test& test){           // copy constructor definition
	cout << "func1" << endl;
}

int main(){
	Test test;
	Func1(test);
}
