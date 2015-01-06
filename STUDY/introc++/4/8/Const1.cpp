/*
 * This program can not compile.
 */
#include <iostream>
using namespace std;

int StrCount(const char* str, char ch){    // added const
	int num = 0;
	for(int i = 0; str[i] != '\0'; ++i){
		if(str[i] = ch){                   // const variable cannot insert.
			++num;
		}
	}
	return num;
}

int main(){
	char path[] = "/home/robert/documents/const.txt";
	cout << "file : " << path << endl;
	cout << StrCount(path, '/') << endl;
}
