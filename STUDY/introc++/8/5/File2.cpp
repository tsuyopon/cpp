#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;

int main(){
	fstream file;

	/*
	 * ios::in     File Input.
	 * ios::out    File Output.
	 * ios::binary Open BinaryMode
	 * ios::trunc  If file exists, file remove and open file.
	 * ios::app    Always, added file.
	 * ios::ate    Open file, and Move position into EOF.
	 */
	file.open("test.txt", ios::in);
	if(!file.is_open()){
		return EXIT_FAILURE;
	}

	string str;
	getline(file, str);
	file.close();
	cout << str << endl;
}
