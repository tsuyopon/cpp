#include "ValueFactory.h"
#include <iostream>
using namespace std;

#define ARRAY_SIZE(array) (sizeof(array) / sizeof*(array))

int main(){
	static const int VALUE[] = {
		1, 2, 4, 8,
	};

	static const int SIZE = ARRAY_SIZE(VALUE);

	ValueFactory factory;

	for(int i = 0; i < SIZE; ++i){
		Value* value = factory.New(VALUE[i]);
		cout << value->Get() << ' ';
		delete value;
	}
	cout << endl;
}
