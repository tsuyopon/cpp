#include<iostream>
using namespace std;

size_t StrLen(char* str){
	int i;
	for( i = 0; *(str +i) != '\0'; ++i){
		cout << *(str+i) << endl;
	}
	return i;
}

void ShowLength(char* str){
	cout << "character: " << str << endl;
	cout << "length: " << StrLen(str) << endl;
}

int main(){
	ShowLength((char *)"Hello");
	ShowLength((char *)"");
}
