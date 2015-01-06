/*
 * test.txtのファイルをopenして１行だけ読み取って、画面上に出力します。
 * Macro3.cppのエラー処理をマクロを使っています。
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// エラー処理をマクロ定義を使ってすっきりさせます。複数行に跨ぐ場合には\を使います。 
#define ON_ERROR_GOTO(expr) \
	error = (expr); \
	if(error != NULL) { \
		goto ON_ERROR; \
	}

const char* Open(ifstream& file, const char* filename){
	file.open(filename);
	return file.is_open() ? NULL : "Could not open file!";
}

const char* GetLine(ifstream& file, string& line){
	getline(file, line);
	return file.fail() ? "Could not read from file!" : NULL;
}

int main(){
	const char* error = NULL;
	ifstream file;
	string line;

	// ファイル先頭付近で定義したマクロ定義を使ってすっきりさせています。
	ON_ERROR_GOTO(Open(file, "test_Macro3.txt"))
	ON_ERROR_GOTO(GetLine(file, line))

	cout << line << endl;
	return EXIT_SUCCESS;

ON_ERROR:
	cerr << error << endl;
	return EXIT_FAILURE;
}
