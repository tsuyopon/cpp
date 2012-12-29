/*
 * このプログラムはコンパイルすることはできますが、実行するとエラーとなります。
 * このように安全でないダウンキャストを実行すると失敗することがあります。
 */
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

string Hoge(ostream& ostr){
	ostringstream& sstr = static_cast<ostringstream&>(ostr);
	sstr.str("");
	sstr << "Hoge" << flush;
	return sstr.str();
}

int main(){
	cout << Hoge(cout) << endl;
}
