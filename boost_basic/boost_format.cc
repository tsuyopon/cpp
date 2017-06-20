#include <iostream>
#include <boost/format.hpp>
using namespace std;

int main()
{
	// %1%が一番目のパラメータ、%2%が二番目のに置き換わります。
	cout << boost::format("%1% %2%") % "hello" % 100 << endl;

	// printfと同じ書式もOK。
	// %05d:0埋めで5桁の整数 %x:16進表記 %f:浮動小数点数 %%:%そのもの
	cout << boost::format("%05d %x %f %%") % 200 % 255 % 3.33 << endl;

	// さらに、%2%と%1%を逆順に使うことも
	cout << boost::format("%2% %1%") % "hello" % 100 << endl;

	// %N$...で順番指定と出力形式指定の合わせ技
	// %04x:0埋めで4桁の16進整数 %s:文字列
	cout << boost::format("%2$04x %1$s") % "hello" % 254 << endl;

	// 文字列である必要はない
	cout << boost::format("%1% = %2%\n") % "1 + 1" % ( 1 + 1 ) << endl;

	// フォーマットされたstringを生成する
	const string s = (boost::format("%2% %1%") % 3 % std::string("Hello")).str();
	cout << s << endl;

	return 0;
}
