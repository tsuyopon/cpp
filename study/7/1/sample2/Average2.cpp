#include "InputStream.h"
#include <iostream>
using namespace std;

bool Average(InputStream& stream){
	int count;
	double avr = 0;

	for(count = 0; stream.Set(); ++count){
		avr += stream.Get();
	}

	if(count == 0){
		return false;
	}

	avr /= count;
	cout << "Average is " << avr << "." << endl;
	return true;
}

int main(){
	while(true){
		InputStream stream;
		if(!Average(stream)){
			break;
		}
	}
}
