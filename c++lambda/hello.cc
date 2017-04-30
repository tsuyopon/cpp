#include<iostream>
#include<string>
using namespace std;

template<typename Func>
void f(Func func){
	func();
}

int main(int argc, char *argv[]) {

	// 1. ラムダ式の文法
	[]	// ラムダキャプチャー
	()	// パラメータ定義節
	{}	// 複合ステートメント
	()	// 関数呼び出し式
	;

	// 2. Hello World
	[]{ std::cout<<"Hello World"<<std::endl;}();

	// 2. ラムダ式を変数に与えることが可能。関数ポインタのようにして呼び出すことが可能
	auto func = []{ cout<<"Hello world from func"<<endl;};
	func();//ラムダ式の呼び出し

	// 3. 引数を与えるラムダ式
	[](string const & str) // 引数の定義
	{       // 関数本体
		cout << str << endl;
	}
	( "I am Argument!");    // 関数呼び出しと引数

	// 4. ラムダ式で戻り値を返す
	auto a = [] { return 0;} (); // 戻り値を推測させる
	auto b = [] () -> float { return 3.14; } (); //明示的に戻り値を定義
	cout << a << endl;
	cout << b << endl;

	// 5. 変数をキャプチャーする
	// ラムダ式は、式が定義される関数のスコープの変数をキャプチャできます。 以下では同じスコープにあるxがキャプチャできています。
	string x = "I am string";
	[&] { cout << x << endl; } (); //参照    (xに値を代入してもコピーと違ってコンパイルエラーにはならない
	[=] { cout << x << endl; } (); //コピー  (xに値を代入するとコンパイルエラーになります

	// 6. ラムダ式を関数に渡す。 fは最初に定義されています。
	f( []{ std::cout<<"Hello world passing to f function"<<std::endl;} );

	return 0;
}
