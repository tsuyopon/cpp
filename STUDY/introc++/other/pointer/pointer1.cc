/*
 * pointerでわかりにくい箇所についてまとめています。
 *
 *
 *
 */
#include<iostream>
using namespace std;

void testFunc(char m[], char *n);

int main(){

	/* [ポイント1]
	 * (1)〜(6)では、(1),(2), (5), (6) と(3),(4)は異なります。(1)と(2)と(5)と(6)は書き換え不可能で同一です。また、(3)と(4)は書き換え可能で同一の意味を表しています。
	 */
	char *s1 = "Hello World";            // (1)  書き換え不可能(コンパイル時にWarningガ表示されるがa.outは生成される)
	const char *s2    = "Hello World";   // (2)  書き換え不可能( (1)でエラーの場合constを付与するとwarningが表示されないようになります)
	char s3[]         = "Hello World";   // (3)  書き換え可能
	char s4[12]       = "Hello World";   // (4)  書き換え可能
	const char s5[]   = "Hello World";   // (5)  書き換え不可能
	const char s6[12] = "Hello World";   // (6)  書き換え不可能

	cout << "s1:" << s1 << endl;
	cout << "s2:" << s2 << endl;
	//cout << "s3:" << s3[] << endl;     // この行はコンパイルエラーとなる
	cout << "s3:" << s3 << endl;
	cout << "s4:" << s4[12] << endl;     // この行は12番目の要素(つまり'\0')が表示される
	cout << "s5:" << s5 << endl;
	cout << "s6:" << s6[12] << endl;     // この行は12番目の要素(つまり'\0')が表示される

	testFunc(s3, s3);

}

void testFunc(char m[], char *n){  // [ポイント2] 関数の引数に対しては m[]でも*nでも同じなので紛らわしい
	cout << "===== testFunc START =====" << endl;
	cout << "m[]:" << m << endl;
	cout << "*n:" << n << endl;
}
