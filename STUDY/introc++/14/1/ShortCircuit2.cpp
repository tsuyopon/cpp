#include<iostream>
#include<string>
using namespace std;

void Show(string* str){
	if( !(str == NULL || str->empty()) ) {
		cout << *str << endl;
	}
}

int main(){
	Show(NULL);    // (1)

	string str;
	Show(&str);    // (2) strはNULLであるのでShow()メソッド内でstr->empty()が実行されないので安全である。

	str = "Hoge";
	Show(&str);    // (3) 
}
