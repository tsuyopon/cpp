#include <iostream>
#define SIZE 5
using namespace std;

template <typename TYPE> void FillArray(TYPE* array, size_t size, TYPE value){
	for(size_t i = 0; i < size; ++i){
		cout << "i = " << i << ", value = " << value << endl;
	}
}

int main(){

	int value = 100;
	int str[SIZE] = { 1, 2, 3, 4, 5 };
	float value2 = 1.0;
	float str2[SIZE] = { 1.0, 2.1, 3.2, 4.3, 5.3 };

	// TYPE is int
	FillArray(str, (size_t)SIZE, value);

	// TYPE is float
	FillArray(str2, (size_t)SIZE, value2);
}
