#include <iostream>
#include <algorithm>

using namespace std;

class IntArray {
	public:
		static const int SIZE = 100;     // const definition
		IntArray();
		int m_array[SIZE];
};

IntArray::IntArray(){
	fill_n(m_array, SIZE, 0);
}

int main(){
	IntArray array;
	cout << array.m_array[IntArray::SIZE - 1] << endl;
}
