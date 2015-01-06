#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int main(){
	const char* error = NULL;
	ifstream file;
	string line;

	file.open("test.txt");
	if(! file.is_open() ){
		error = "Could not open file";
		goto ON_ERROR;
	}

//	string line;          /* Don't wirte this line here */
	getline(file, line);
	if(file.fail()){
		error = "Could not read from file";
		goto ON_ERROR;
	}

	return EXIT_SUCCESS;

ON_ERROR:
	cerr << error << endl;
	return EXIT_FAILURE;
}

