#include "Array.h"
#include <iostream>
using namespace std;

int main(){
	Array<int> array(5);

	for(int i = 0, size = array.Size(); i < size; ++i){
		array.Set(i, i*2);
	}
	for(int i = 0, size = array.Size(); i < size; ++i){
		cout << array.Get(i) << ' ';
	}
	cout << endl;
}
