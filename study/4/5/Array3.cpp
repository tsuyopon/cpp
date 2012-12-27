#include<iostream>
using namespace std;

int main(){
	char array[10];
	cout << "array   : " << (size_t)array << endl;
	for(int i = 0; i < 10; i++){
		cout << "&array[" << i << "] : " << (size_t)&array[i] << endl;
	}
}
