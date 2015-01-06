/*
 * test.txtのファイルをopenして１行だけ読み取って、画面上に出力します。
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// ファイルを開きます。
const char* Open(ifstream& file, const char* filename){
	file.open(filename);
	return file.is_open() ? NULL : "Could not open file!";
}

// ファイルから一行取得します。
const char* GetLine(ifstream& file, string& line){
	getline(file, line);
	return file.fail() ? "Could not read from file!" : NULL;
}

int main(){
	const char* error = NULL;
	ifstream file;
	string line;

	error = Open(file, "test_Macro3.txt");
	if( error != NULL ){
		goto ON_ERROR;
	}

	error = GetLine(file, line);
	if(error != NULL){
		goto ON_ERROR;
	}

	cout << line << endl;
	return EXIT_SUCCESS;

ON_ERROR:
	cerr << error << endl;
	return EXIT_FAILURE;
}
