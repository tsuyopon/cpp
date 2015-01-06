/*
 * NDEBUGをdefineとして定義するとassertを無視してくれます。これはリリースモードとデバッグモードを分離できることを意味します。
 * 今回はMakefileによってこれらの出し分けを行っています。
 */

#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <iostream>
using namespace std;

const int INTARRAY_SIZE = 10;

class IntArray {
	public:
		int m_array[INTARRAY_SIZE];
		IntArray();
		int Get(int i);
		void Set(int i, int value);
		void CheckIndex(int i);
		void Process();
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
	assert(0 <= i && i < INTARRAY_SIZE);
	// assertマクロを利用する前までは、以下のロジックを記載していた。
	/*
	if( 0 <= i && i < INTARRAY_SIZE){
		// OK
		cout << "OK: i=" << i << endl;
	} else {
		cout << "Index Number is Invalid." << endl;
		exit(EXIT_FAILURE);
	}
	*/
}

void IntArray::Process(){
}

int main(){
	int i;
	IntArray obj;
	for(i = 0; i < 100; i++){
		cout << i << endl;
		obj.Set(i, i);
	}

	return true;
}
