#include "InputStream.h"
#include <iostream>
using namespace std;

int main(){
	InputStream stream;
	cout << "> " << flush;
	stream.Set();
	const Stream& ref = stream;
	cout << ref.Get() << endl;
}
