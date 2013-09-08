#include<iostream>
#include<stdexcept>

using namespace std;

#define ARRAY_SIZE(array) (sizeof (array) / sizeof *(array) )

double Average(const int* array, size_t size){

// equals #ifndef
#if ! defined(NDEBUG)
	cout << "NDEBUG NOT DEFINED. SO NULL CHECK START" << endl;
	if( array == NULL ){
		throw invalid_argument("Invalid Argument passed to Average method");
	}
#endif

	int sum = 0;
	for(size_t i = 0; i < size; ++i){
		sum += array[i];
	}

	return static_cast<double>(sum) / size;
}

int main(){
	int value[] = { 12, 56, 23, 93, 84, 45, 77, 87, 100, 45 };
	cout << "Average: " << Average(value, ARRAY_SIZE(value)) << endl;
}
