#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class IntArray {
	public:
		IntArray(int size);
		~IntArray();

	public:
		int Get(int i);
		void Set(int i, int value);

	private:
		void CheckIndex(int i);

	private:
		int* m_array;
		int m_size;
};

// Constructor
IntArray::IntArray(int size){
	m_array = new int[size];
	m_size = size;
	cout << "Constructor called. Element num = " << m_size << endl;
}

IntArray::~IntArray(){
	delete [] m_array;
	cout << "Destructor called Element num = " << m_size << endl;
}

// Get Method
int IntArray::Get(int i){
	CheckIndex(i);
	return m_array[i];
}

// Set Method
void IntArray::Set(int i, int value){
	CheckIndex(i);
	m_array[i] = value;
}

// Index Number Checking.
void IntArray::CheckIndex(int i){
	if( 0 <= i && i < m_size){
		// OK
		cout << "OK: i=" << i << endl;
	} else {
		cout << "Index Number is Invalid." << endl;
		exit(EXIT_FAILURE);
	}
}

// Display
void Viss(int num){
	cout << "Viss: No." << num << endl;
}

IntArray a(10);

int main(){
	Viss(1);

	IntArray b(20);
	Viss(2);

	IntArray c(30);
	Viss(3);

	{
		IntArray d(40);
		Viss(4);
	}

	Viss(5);
}
