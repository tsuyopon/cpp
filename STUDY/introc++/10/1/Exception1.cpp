#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int main(){
	ifstream file;
	file.open("test.txt");
	if( !file.is_open() ){
		cerr << "Could not open file" << endl;
		return EXIT_FAILURE;
	}

	string line;
	getline(file, line);
	if(file.fail()){
		cerr << "Could not read from file" << endl;
		return EXIT_FAILURE;
	}

	cout << line << endl;

}

