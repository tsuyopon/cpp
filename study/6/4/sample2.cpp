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

	Integer array[4] = {
		Integer(),
		Integer(3),
		Integer(9),
	};

	array[0].Show();
	array[1].Show();
	array[2].Show();

}
