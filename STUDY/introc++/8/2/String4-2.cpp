#include<string>
#include<iostream>
using namespace std;

int main(){
	string text="helloworld";

	// size
	cout << "size(): " << text.size() << ", length(): " << text.length() << endl;

	// resize
	text.resize(8);
	cout << "text.resize(8) executed: " << text << endl;

	// dynamic memory capacity
	cout << "capacity: " << text.capacity() << endl;

	// insert
	text.insert(0 /* pos */, "g");
	cout << text << endl;

	// erace
	text.erase(1 /*pos */, 2 /*npos*/);  // "ghellowor" of "he" will match.
	cout << text << endl;

	// replace
	text.replace(0 /* pos */, 2/*npos*/, "rr"); // "gllowor" become "rrlowor". "gl" replaces "rr".

	// find
	string::size_type pos = text.find("lowor", 0);
	if( pos == string::npos ){
		cout << "Not matched" << endl;
	} else {
		cout << "matched pos=" << pos << endl;
	}

	// rfind(reverse find)  search from tail.
	string::size_type rpos = text.rfind("o", text.size());
	if( rpos == string::npos ){
		cout << "Not matched" << endl;
	} else {
		cout << "matched rpos=" << rpos << endl;
	}

	// substr
	string substr1 = text.substr(1 /*pos*/, 2/*npos*/);
	cout << "substr:" << substr1 << endl;

	// convert character address with null terminator
	const char* str;
	str = text.c_str();
	cout << "c_str(): " << str << endl;

	// convert empty
	text.clear();
	if( text.empty() ){
		cout << "text is empty" << endl;
	} else {
		cout << "text is not empty" << endl;
	}


}
