/*
 * this program device accesss control version from sample1.cc
 */
#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;

const int INTARRAY_SIZE = 10;

// Divide Access Class into public and private
class IntArray {
	public:
		IntArray();
		int Get(int i);
		void Set(int i, int value);
	private:
		void CheckIndex(int i);
		int m_array[INTARRAY_SIZE];   // Array
};

// Constructor
IntArray::IntArray(){
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
	if( 0 <= i && i < INTARRAY_SIZE){
		// OK
		cout << "OK: i=" << i << endl;
	} else {
		cout << "Index Number is Invalid." << endl;
		exit(EXIT_FAILURE);
	}
}

int main(){
	int i;
	IntArray obj;
	for(i = 0; i < 100; i++){
		obj.Set(i, i);
	}

	return true;
}
