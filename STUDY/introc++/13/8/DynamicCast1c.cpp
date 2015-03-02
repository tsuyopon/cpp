#include<iostream>
#include<sstream>
#include<string>
using namespace std;

/* DynamicCast1.cppでは参照をdynamic_castしていました。
 * しかし、今回の場合にはポインタをdynamic_castしています。
 * この場合にはダウンキャストに失敗した場合bad_cast例外ではなく代わりにNULLポインタがかえってきます。
 *
 */
string Hoge(ostream& ostr){
	ostringstream* sstr = dynamic_cast<ostringstream*>(&ostr);
	if(sstr != NULL){
		sstr->str("");
		*sstr << "Hoge" << flush;
		return sstr->str();
	} else {
		return "Error!";
	}
}

int main(){
	ostringstream sstr;
	cout << Hoge(sstr) << endl;  // 成功する
	cout << Hoge(cout) << endl;  // 失敗する
}
