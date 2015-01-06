#include<iostream>
using namespace std;

size_t StrLen(char* str){
	char *p;
	for( p = str; *p != '\0'; ++p){
		cout << p << endl;
		// do nothing.
	}
	return p - str;
}

void ShowLength(char* str){
	cout << "character: " << str << endl;
	cout << "length: " << StrLen(str) << endl;
}

int main(){
	ShowLength((char *)"Hello");
	ShowLength((char *)"");
}
