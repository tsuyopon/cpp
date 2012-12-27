#include <iostream>
using namespace std;

void One(int& ret){
	int n = 1;
	ret = n;
}

int main(){
	int ret;
	One(ret);
	cout << ret + 2 << endl;
}
