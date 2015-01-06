#include <iostream>
using namespace std;

class Integer {
	public:
		int m_value;
		Integer();
		Integer(int num);
		void Show();
};

// Constructer
Integer::Integer()        { m_value = 0; }    // Default Constructer
Integer::Integer(int num) { m_value = num; }  // Constructor's Overload

// method
void Integer::Show()      { cout << m_value << endl; }

int main(){
	Integer a;              // Don't write "Integer a();".
	Integer b(100), c(40);

	a.Show();
	b.Show();
	c.Show();
}
