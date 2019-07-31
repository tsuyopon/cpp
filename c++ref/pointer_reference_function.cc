// 関数を実装する際に戻り値としてポインタを返すべきか、参照を返すべきか悩んだ場合にはこのプログラムを参照すること
// 基本的にはポインタを返して、参照で受け取っても動作自体には問題ないが、その場合には無駄なコピーコンストラクタが呼ばれることに注意すること

#include <iostream>
using namespace std;
class Hoge
{
public :
	Hoge(){cout << "デフォルト・コンストラクタ" << endl;}
	Hoge(const Hoge & obj){cout << "コピー・コンストラクタ" << endl;}
};
Hoge x;

//値と参照を返す関数
Hoge   get_val(){return x;}
Hoge & get_ref(){return x;}

int main()
{
	cout << endl << "### 値返し" << endl;
	cout << "値で受け取り" << endl;
	Hoge   x_val = get_val();
	cout << "参照で受け取り" << endl;
	const Hoge & y_val = get_val();

	cout << endl << "### 参照返し" << endl;
	cout << "値で受け取り" << endl;
	Hoge   x_ref = get_ref();
	cout << "参照で受け取り" << endl;
	const Hoge & y_ref = get_ref();

	return 0;
}
