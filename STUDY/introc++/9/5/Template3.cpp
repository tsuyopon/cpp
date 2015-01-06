#include <iostream>
#include <string>
using namespace std;

template <typename TYPE> void FillArray(TYPE* array, size_t size, TYPE value){
	for(size_t i = 0; i < size; ++i){
		array[i] = value;
	}
}

template <typename TYPE> void ShowArray(const TYPE* array, size_t size){
	for(size_t i=0; i < size; ++i){
		cout << array[i] << endl;
	}
}

int main(){
	const int SIZE = 3;
	string str[SIZE];

	FillArray<string>(str, SIZE, "hoge");
	ShowArray(str, SIZE);
}
