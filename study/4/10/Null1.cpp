#include <iostream>
using namespace std;

/*
 * "const char* p;" とすると参照先が定数となる。p自体は定数はならない。
 * "char* const p = &a;" とするとポインタpが定数になる
 * 上記両方を定数にしたい場合には "const char* const p"とすればよい
 */
const char* const MONTH_NAME[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", "July", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// 関数ポインタを定数とする
const char* GetOldMonthName(int month){
	if( (1 <= month) && (month <= 12) ){
		return MONTH_NAME[month-1];
	}
	return 0;   // 0 equals NULL
}

int main(){
	int month;
	cout << "What month is it now? > " << flush;
	cin >> month;

	const char* name = GetOldMonthName(month);
	if(name == 0){
		cout << "input error" << endl;
	} else {
		cout << name << endl;
	}
}
