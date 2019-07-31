//  sample3_1.ccでlvalueによりコピーコンストラクタを呼び出し、
//  sample3_2.ccでrvalueによりmoveコンストラクタを呼び出した。
//  sample3_1.ccのlvalueを引き渡しコピーコンストラクタで、先ほどのsample3_2のmoveコンストラクタのすげ替え書rをおこなったらどうなるかを確認する。
//
//  注意: このプログラムはポインタのすげ替えはread-onlyなオブジェクトでできないとのことでコンパイル自体失敗します。
/**
$ g++ -std=c++11 sample3_3.cc 
sample3_3.cc: In copy constructor 'X::X(const X&)':
sample3_3.cc:27:9: error: assignment of member 'X::ptr' in read-only object
   r.ptr = nullptr ;
         ^
**/

#include <iostream>
#include <algorithm>

class X
{
private :
	char * ptr ;

public :
	X() {
		std::cout << "constructor(" << this << ")" << std::endl;
		ptr = new char[1000] ;
		// バッファに対して、時間のかかる書き込みを実行
	}

/*** rvalueでコピーコンストラクタが呼ばれ、その中でポインタのすげ替え処理を行おうとする ***/
	// コピーコンストラクタ
	X( X const & r ) {
		std::cout << "copy constructor(" << this << ")" << " <- " << &r << std::endl;
		ptr = r.ptr ;
		r.ptr = nullptr ;
	}

/** sample3_2.ccで呼ばれていたMove
	// Move コンストラクタ
	X( X && r ) {
		std::cout << "move constructor(" << this << ")" << " <- " << &r << std::endl;
		ptr = r.ptr ;
		r.ptr = nullptr ;
	}
**/

	// デストラクタ
	~X() {
		std::cout << "destructor(" << this << ")" << std::endl;
		delete[] ptr ;
	}
} ;

X f(){ return X() ; }

int main()
{
	// 関数の戻り値はrvalueである。
	X a( f() ) ; // 1.

	X tmp ; 
	//X b( tmp ) ; // 2.  下記のように明示的にcastすることで"copy constructor"から"move constructor"を呼び出すようになる。
	// (sample3_1.ccとsample3_2.ccを比較して、実行してみることをおすすめする
	X b( tmp ) ;   // もしくは左記のコードは「X b( std::move(tmp) ) ;」と等価。つまりlvalueをrvalueにキャストしている。

	// これ以降、tmpはもう使わない。
}
