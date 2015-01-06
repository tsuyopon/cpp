#include<iostream>
using namespace std;

int main(){
	int flag;

	cout << "Enter 1 or 0 > " << flush;
	cin >> flag;

	flag = 1 - flag;

	//上記コードはflagが0と1しか入らないことが保証されていれば、以下と同様です。
	/* 
	if( flag == 1 ){
		flag = 0;
	} else {
		flag = 1;
	}
	*/

	cout << flag << endl;

	return true;

}
