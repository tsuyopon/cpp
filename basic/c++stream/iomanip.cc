#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	cout << setw(10) << "dec"
		<< setw(10) << "hex"
		<< setw(10) << "oct" << endl;
	for( int i = 0; i < 10 ; i++){
		cout << dec << setw(10) << i
			<< hex << setw(10) << i
			<< oct << setw(10) << i << endl;
	}
	return EXIT_SUCCESS;
}
