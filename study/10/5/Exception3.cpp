#include <iostream>
using namespace std;

void Error(){
	try {
		throw 1;
	} catch (int error){
		cerr << "catched by case1" << endl;
		throw "Error";
	} catch (const char* error){
		cerr << "catched by case2" << endl;
	}
}

int main(){
	try{
		Error();
	} catch (const char* error) {
		cerr << "catched by main" << endl;
	}
}

