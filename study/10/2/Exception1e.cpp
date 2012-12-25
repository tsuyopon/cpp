#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int main(){
	try {
		ifstream file;
		file.open("test.txt");
		if(! file.is_open() ){
			throw "Could not open file";
		}

		string line;
		getline(file, line);
		if(file.fail()){
			throw "Could Not read from file";
		}

		cout << line << endl;
	} catch (const char* error) {
		cerr << error << endl;
		return EXIT_FAILURE;
	}
}
