#include<iostream>
using namespace std;

void Error(){
	int* p = NULL;

	try {
		p = new int[10];
		throw "Error Occurerd";
		delete[] p;
	} catch(...){
		cerr << "release memory" << endl;
		delete[] p;
		throw;
	}
}

int main(){
	try{
		Error();
	} catch(const char* error){
		cerr << "main:" << error << endl;
	}
}
