// boost::functionにおけるサンプル
#include <iostream>
#include <functional>
#include <boost/function.hpp>
using namespace std;

struct SomeObject
{
	SomeObject( int i_n ) : n( i_n ) {}
	int Do( int x ) { return x*n; }
	const int n;
};

bool f( int x, int y )
{
	return x*x < y;
}

int main()
{
	// intとintを取ってboolを返す２引数関数を格納できる関数オブジェクト
	// とりあえず普通の関数を入れてみる。
	boost::function<bool (int, int)> cmp = &f;
	if( cmp(4, 20) )
	{
		cout << 1 << endl;
	}

	// 途中で関数オブジェクトを突っ込んでみたりする
	cmp = std::not2( std::less<int>() );
	if( cmp(4, 20) )
	{
		cout << 2 << endl;
	}

	// intを取ってintを返す関数。
	// std::binder1st< std::mem_fun1_t<int,SomeObject,int> >
	// などというワケわからん型の変数で受け取らなくても保持できる
	SomeObject t( 3 );
	boost::function<int (int)> g =
		std::bind1st( std::mem_fun(&SomeObject::Do), &t );
	if( 45 == g(15) )
	{
		cout << 3 << endl;
	}

	return 0;
}
