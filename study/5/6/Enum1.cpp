#include<iostream>
using namespace std;

enum CompareResult{
	CR_LESS_THAN = 0,
	CR_EQUAL_TO  = 1,
	CR_GREATER_THAN = 2,
};

// この関数でレスポンスする型はenum上で定義された値でなければなりません。
CompareResult Compare(int a, int b){
	if(a < b){
		return CR_LESS_THAN;
	} else if( a > b){
		return CR_GREATER_THAN;
	} else {
		return CR_EQUAL_TO;
	}
}

bool Compare(){
	int a, b;
	cout << "Input Two Number > " << flush;
	cin >> a >> b;

	if( a == -1 ){
		return false;
	}

	switch(Compare(a, b)){
		case CR_LESS_THAN:
			cout << "a less than b" << endl;
			break;
		case CR_EQUAL_TO:
			cout << "a and b are equal" << endl;
			break;
		case CR_GREATER_THAN:
			cout << "a is greater than b" << endl;
			break;
	}
	return true;
}

int main(){
	while(Compare()){
		// do nothing.
	}
}

