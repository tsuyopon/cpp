#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int WIDTH = 16;

int main(){
	fstream file;
	file.open("hello.txt", ios::in | ios::binary);
	if(!file.is_open()){
		return EXIT_FAILURE;
	}
	do{
		unsigned char buf[WIDTH];
		file.read( (char*)buf, sizeof buf);
		for(int i = 0, size = file.gcount(); i < size; ++i){
			printf("%02X", buf[i]);
		}
	} while(!file.eof());
	file.close();
}
