/* このプログラムはエラーになります。 
 * コンパイル時に15, 18, 21行目の参照でのみエラーとなっていて、12、14、17、20行目ではエラーが出ていないことに着目してください。
 */

#include<iostream>
using namespace std;

int main(){
	char   c = '1';
	int    i = 2;
	double d = 3;
	void* p;             // void型のへのポインタ宣言

	p = &c;              // void型への代入
	cout << *p << ' ';   // void型ポインタの参照

	p = &i;
	cout << *p << ' ';

	p = &d;
	cout << *p << endl;
}
