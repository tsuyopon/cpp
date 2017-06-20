// rvalueとlvalueのメリットが分かるプログラム
// このプログラムではコピーコンストラクタがコンストラクタで行った処理と同様のをすべてstd::copyしている。ただの付替えをするだけ。
// しかし、これを改良したsample3_2.ccではムーブコンストラクタを使ってポインタを付け替えるだけで済むようにしている。
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

	// コピーコンストラクタ
	X( X const & r ) {
		std::cout << "copy constructor(" << this << ")" << " <- " << &r << std::endl;
		ptr = new char[1000] ;
		std::copy( &ptr[0], &ptr[1000], &r.ptr[0] ) ;
	}

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
	X b( tmp ) ; // 2.

	// これ以降、tmpはもう使わない。
}
