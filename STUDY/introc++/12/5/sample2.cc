/*
 *  代替トークンに関するサンプルです。
 *
 */
#include <iostream>
using namespace std;

// "#"は"%:"と表すことができる
// "##"は"%:%:"と表すことができる。
%:define TEST 111; 

int main()
<%   // "{"は"<%"と表すことができる

	cout << "ALTERNATIVE TOKEN START" << endl;

	// "[" は "<:"と表すことができる。"]"は":>"と表すことができる。
	int a<:5:>;
	a<:0:> = 100;
	cout << a<:0:> << endl;

	// "&&"は"and"と表すことができる
	if( 1 and 1 ){
		cout << "and ok" << endl;
	}

	// "||"は"or"と表すことができる
	if( 1 or 1 ){
		cout << "or ok" << endl;
	}

	// "!"は"not"と表すことができる
	if(not false){
		cout << "not ok" << endl;
	}

	// "!="は"not_eq"と表すことができる
	if(1 not_eq 0){
		cout << "not_eq ok" << endl;
	}

	// "^"は"xor"と表すことができる
	if( 1 xor 0){
		cout << "xor ok" << endl;
	}

	// "&"は"bitand"と表すことができる
	cout << "bitand: " << (1 bitand 1 )<< endl;

	// "|"は"bitor"と表すことができる
	cout << "bitor: " << (1 bitor 1 )<< endl;

	// "~"は"compl"と表すことができる
	cout << "compl:" << (compl 128) << endl;

	int flags = 6;  // (0110)[2進数]
	int flags1, flags2, flags3, flags4;

	flags1 = flags;
	flags2 = flags;
	flags3 = flags;
	flags4 = flags;

	// "&="は"and_eq"と表すことができる
	flags1 and_eq 5;  // 5 = (0101)[2進数]
	cout << "and_eq:" << flags1 << endl;

	// "|="は"or_eq"と表すことができる
	flags2 or_eq 5;  // 5 = (0101)[2進数]
	cout << "or_eq:" << flags2 << endl;

	// "^="は"xor_eq"と表すことができる
	flags3 xor_eq 5;  // 5 = (0101)[2進数]
	cout << "xor_eq:" << flags3 << endl;

%>   // "}"は"%>"と表すことができる
