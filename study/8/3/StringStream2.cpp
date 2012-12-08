#include<iostream>
#include<sstream>
using namespace std;

int main(){
	stringstream sstr("1 2");
	int x, y;

	sstr >> x >> y;
	cout << x << " + " << y << " = " << (x + y) << endl;
}
