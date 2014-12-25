#include<iostream>
#include<cstdlib>

using namespace std;

int main(){
	int n;
	cout << "ENTER YOUR INPUT > " << flush;
	cin >> n;
	return cin.fail() ? EXIT_FAILURE : EXIT_SUCCESS;
}
