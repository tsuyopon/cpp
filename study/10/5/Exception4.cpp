#include<iostream>
using namespace std;

void Error(){
	int* p = NULL;
	try {
		p = new int[10];
		throw "Error Occured!";
		delete[] p;
	} catch(const char* error){
		cerr << "release memory" << endl;
		delete[] p;
		throw error;
	}
}

int main(){
	try {
		Error();
	} catch(const char* error){
		cerr << "main:" << error << endl;
	}
}
