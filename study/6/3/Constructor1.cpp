#include<iostream>
using namespace std;

// Class Definition
class Integer {
	public:
		int m_value;
		Integer();
		void Show();
};

// Constructor
Integer::Integer(){
	m_value = 0;
}

// Display Member Variable
void Integer::Show(){
	cout << m_value << endl;
}

int main(){
	Integer a, b, c;
	a.Show();
	b.Show();
	c.Show();
}
