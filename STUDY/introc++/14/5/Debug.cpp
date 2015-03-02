#include "Debug.h"

#ifdef NDEBUG  // リリース

#else          // デバッグ

#include <iostream>
#include <cstdlib>
using namespace std;

namespace Debug {
	void Assert(bool b, const char* file, int line){
		if(b){
		} else {
			cerr << file << '(' << line << ")" << ": Assertion Error!" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

#endif         // #ifndef NDEBUG

int main(){
	ASSERT(false);
}
