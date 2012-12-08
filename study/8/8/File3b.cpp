#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(){
	fstream file;
	file.open("binary.txt", ios::in|ios::binary);
	if(!file.is_open()){
		return EXIT_FAILURE;
	}

	int n;
	file.read((char*)&n, sizeof(n));
	file.close();

	cout << n << endl;
}

