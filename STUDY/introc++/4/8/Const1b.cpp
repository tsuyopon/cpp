#include <iostream>
using namespace std;

int StrCount(char* str, char ch){
	int num = 0;
	for(int i = 0; str[i] != '\0'; ++i){
		if(str[i] = ch){                   // This assignment must be "==". 
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
