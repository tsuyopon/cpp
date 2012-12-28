#include <iostream>
using namespace std;

#define TIMES(cnt, n) for(int cnt = 0; cnt < n; ++cnt)

int main(){
	TIMES(i, 5){
		cout << i << ' ';
	}
	cout << endl;
}
