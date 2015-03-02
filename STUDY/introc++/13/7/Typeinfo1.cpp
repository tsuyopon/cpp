#include<iostream>
#include<fstream>
#include<sstream>
#include<typeinfo>
using namespace std;

/*
 * typeidは実行時に実際に渡されてきたオブジェクトの本来の型情報です。
 * 実行時に動的に得られる型情報のことをRTTI(Run-Time Type Information: 実行時型情報)といいます。
 */
void ShowType(const ostream& ostr){
	cout << typeid(ostr).name() << endl;
}

int main(){
	fstream       fstr;
	ofstream      ofstr;
	stringstream  sstr;
	ostringstream osstr;

	ShowType(cout);
	ShowType(fstr);
	ShowType(ofstr);
	ShowType(sstr);
	ShowType(osstr);
}
