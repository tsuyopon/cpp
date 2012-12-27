/*
 * sample2改良版です。
 *
 * <usage>
 *  $ ./a.out
 *   1 2 3 -1
 */
#include "InputStream.h"
#include <iostream>
using namespace std;

int main(){

	// Stream
	Stream stream;
	stream.Set();
	cout << stream.Get() << endl;

	// InputStream
	InputStream istream;
	cout << "> " << flush;
	istream.Set();
	cout << istream.Get() << endl;

}
