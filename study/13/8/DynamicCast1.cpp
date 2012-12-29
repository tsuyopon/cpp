/*
 * このプログラムはコンパイルすることはできますが、実行するとエラーとなります。
 * このように安全でないダウンキャストを実行すると失敗することがあります。
 */
#include<iostream>
#include<sstream>
#include<string>
#include<typeinfo>
using namespace std;

string Hoge(ostream& ostr){

	try {
		ostringstream& sstr = dynamic_cast<ostringstream&>(ostr);
		sstr.str("");
		sstr << "Hoge" <<flush;
		return sstr.str();
	} catch(const bad_cast& e){
		return "Error!";
	}
}

int main(){
	ostringstream sstr;
	cout << Hoge(sstr) << endl;  // 成功する
	cout << Hoge(cout) << endl;  // 失敗する
}
