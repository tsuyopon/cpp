/*
 * 実行はできますが、正常には動作しません。
 * override2_2.cppに改良版があります。
 *
 * <usage>
 *  $ ./a.out
 *   1 2 3 -1
 */
#include "InputStream.h"
#include "ArrayStream.h"
#include <iostream>
using namespace std;

bool Average(Stream& stream){
	int count;
	double avr = 0;

	for( count = 0; stream.Set();  ++count ){
		avr += stream.Get();
	}

	if( count == 0 ){
		return false;
	}

	avr /= count;
	cout << "Average is " << avr << "." << endl;
	return true;
}

int main(){

	// InputStream
	InputStream istream;
	Average(istream);

	// ArrayStream
	static const double ARRAY[] = { 0.5, 1.5, -1};
	ArrayStream astream(ARRAY);
	Average(astream);
}
