/*
 * ビットフラグの仕組みに関するサンプルです。
 * ここではビットフラグ同士の合成、削除、反転を行います。
 *
 */
#include <iostream>
using namespace std;

int Bit(int x){
	return 1 << x;
}

const int SHOW_X = Bit(0);
const int SHOW_Y = Bit(1);
const int SHOW_Z = Bit(2);

void Show(int flags){
	cout << ( ( flags & SHOW_X) != 0 ? 'X' : 'x')
		 << ( ( flags & SHOW_Y) != 0 ? 'Y' : 'y')
		 << ( ( flags & SHOW_Z) != 0 ? 'Z' : 'z')
		 << endl;
}

int main(){

	int flags1 = 0;
	int flags2 = SHOW_Y;
	int flags3 = SHOW_X|SHOW_Z;
	int flags4 = SHOW_X|SHOW_Y|SHOW_Z;

	// 通常のビット加工をしない場合の出力
	cout << "NORMAL" << endl;
	Show(flags1);
	Show(flags2);
	Show(flags3);
	Show(flags4);

	// 追加。ここではSHOW_Xフラグをたてます。なお、既にbitがたっている場合には何もしません。
	// "flags1 = flags1 | SHOW_X" は"flags1 != SHOW_X"の様に記述することもできます。
	cout << "ADDED FLAG" << endl;
	Show(flags1|SHOW_X);
	Show(flags2|SHOW_X);
	Show(flags3|SHOW_X);
	Show(flags4|SHOW_X);

	// 追加。SHOW_X, SHOW_Y, SHOW_Zフラグをすべてたてる
	Show(flags1|SHOW_X|SHOW_Y|SHOW_Z);

	// 削除。SHOW_Xフラグがあれば削除します。なお、bitフラグがたっていなければ何もしません。
	int dflags1, dflags2, dflags3;
	cout << "DELETE FLAG" << endl;
	dflags1 = flags1;
	dflags2 = flags2;
	dflags3 = flags3;
	dflags1 &= ~SHOW_X;
	dflags2 &= ~SHOW_X;
	dflags3 &= ~SHOW_X;
	Show(dflags1);
	Show(dflags2);
	Show(dflags3);

	// 削除。SHOW_X, SHOW_Y, SHOW_Zフラグをすべて削除する
	int dflags4;
	dflags4 = flags4;
	dflags4 &= ~(SHOW_X|SHOW_Y|SHOW_Z); 
	Show(dflags4);

	// 反転。SHOW_Xフラグを反転させます。
	int rflags1, rflags2, rflags3;
	cout << "REVERSE FLAG" << endl;
	rflags1 = flags1;
	rflags2 = flags2;
	rflags3 = flags3;
	rflags1 ^= SHOW_X;
	rflags2 ^= SHOW_X;
	rflags3 ^= SHOW_X;
	Show(rflags1);
	Show(rflags2);
	Show(rflags3);

	// 反転。SHOW_X, SHOW_Y, SHOW_Zフラグをすべて反転する
	int rflags4;
	rflags4 = 0;
	rflags4 ^= SHOW_X|SHOW_Y|SHOW_Z;
	Show(rflags4);


}
