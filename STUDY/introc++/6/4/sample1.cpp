#include <iostream>
using namespace std;

class Integer {
	public:
		int m_value;
		Integer(int num = 0);
		void Show();
};

// Constructer
Integer::Integer(int num) { m_value = num; }

// method
void Integer::Show()      { cout << m_value << endl; }

int main(){
	Integer a;
	Integer b(100), c(40);

	a.Show();
	b.Show();
	c.Show();
}
