#include<iostream>
#include<cstdlib>
#include<cstring>

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

IntArray::IntArray(int size){
	m_array = new int[size];
	m_size = size;

	cout << "called constructer. element count is " << m_size << endl;
}

IntArray::~IntArray(){
	delete [] m_array;
	cout << "called destructer. element count is " << m_size << endl;
}

int IntArray::Get(int i){
	CheckIndex(i);
	return m_array[i];
}

void IntArray::Set(int i, int value){
	CheckIndex(i);
	m_array[i] = value;
}

void IntArray::CheckIndex(int i){
	if( 0 <= i && i < m_size ){
		// ok
	} else {
		cout << "index is invalid. value=" << i << endl;
		exit(EXIT_FAILURE);
	}
}

int main(){
	return true;
}
