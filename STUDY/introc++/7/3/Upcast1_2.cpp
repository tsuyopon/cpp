/*
 * This program can not compile.
 * This must be upcast.
 */
#include "InputStream.h"
#include <iostream>
using namespace std;

int main(){
	InputStream stream;
	cout << "> " << flush;
	Stream& ref = stream;
	ref.Set();                   // Could not call Set member method
	cout << ref.Get() << endl;
}
