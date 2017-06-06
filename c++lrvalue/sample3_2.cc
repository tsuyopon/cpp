// rvalueとlvalueのメリットが分かるプログラム
// このプログラムはsample3_1.ccの改良版である。
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

	// Move コンストラクタ   /************ この処理を追加  ***************/
	X( X && r ) {
		std::cout << "move constructor(" << this << ")" << " <- " << &r << std::endl;
		ptr = r.ptr ;
		r.ptr = nullptr ;
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
	//X b( tmp ) ; // 2.  下記のように明示的にcastすることで"copy constructor"から"move constructor"を呼び出すようになる。
	// (sample3_1.ccとsample3_2.ccを比較して、実行してみることをおすすめする
	X b( static_cast<X &&>(tmp) ) ;   // もしくは左記のコードは「X b( std::move(tmp) ) ;」と等価。つまりlvalueをrvalueにキャストしている。

	// これ以降、tmpはもう使わない。
}
