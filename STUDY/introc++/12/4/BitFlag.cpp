/*
 * ビットフラグの仕組みに関するサンプルです。
 * fopen 等で指定されるビットフラグの仕組みみたいなものでしょう。
 *
 */
#include <iostream>
using namespace std;

int Bit(int x){
	return 1 << x;
}

const int SHOW_X = Bit(0);
const int SHOW_Y = Bit(1);
const int SHOW_Z = Bit(2);

void Show(int flags){
	cout << ( ( flags & SHOW_X) != 0 ? 'X' : 'x')
		 << ( ( flags & SHOW_Y) != 0 ? 'Y' : 'y')
		 << ( ( flags & SHOW_Z) != 0 ? 'Z' : 'z')
		 << endl;
}

int main(){
	Show(0);                     // 引数は0(=000)
	Show(SHOW_Y);                // 引数は10(=010)
	Show(SHOW_X|SHOW_Z);         // 引数は101
	Show(SHOW_X|SHOW_Y|SHOW_Z);  // 引数は111
}
