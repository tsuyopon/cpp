#include<iostream>
#include<string>

using namespace std;
string strtolower(string str);

int main(){
	cout << strtolower("abcdefghijklmnopqrstuvwxyz") << endl;
	cout << strtolower("ABCDEFGHIJKLMNOPQRSTUVWXYZ") << endl;
	cout << strtolower("0123456789") << endl;
}

string strtolower(string str){
	int len = str.length();
	for(int i = 0; i < len; i++){
		if(65<=str[i] && str[i] <= 90){  // from A to Z
			str[i] += 32;                // convert lower character
		}
	}
	return str;
}
