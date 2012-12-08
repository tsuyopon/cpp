#include<iostream>
#include<string>

using namespace std;

int main(){
	string hello = "hello";
	hello = "Hello";
	hello += " World";                                   //Remark: +=

	cout << "Character:" << hello << endl;
	cout << "Code:";
	for(int i = 0, size = hello.size(); i < size; i++){
		cout << (int)(unsigned char)hello[i] << ", ";    // Remark: hello[i]
	}
	cout << endl;

}

