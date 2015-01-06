/*
 * http://www.g-ishihara.com/c_dt_01.htm
 *
 */
#include <iostream>
#include <string>
using namespace std;

void testFunc(char* aaa);

int main(){
	string url;
	url = "http://www.yahoo.co.jp";
	testFunc(url.c_str());
}

// if we want to compile, add const target in front of char*
void testFunc(char* aaa){
	cout << "OKOK" << endl;
}
