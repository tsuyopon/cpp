#include "Stream.h"
#include <iostream>
using namespace std;

double Stream::Get() const {
	return m_n;
}

bool Stream::Set() {
	SetBase();
	return m_n >= 0;
}

/*
 * 派生クラスのSetBase()を呼び出すためには、基底クラスにもSetBase()が存在しないとコンパイルエラーを起こします。
 * これでは、非常に不便です。
 * そこで、純粋仮想関数「virtual void SetBase() = 0」をヘッダファイルに定義すると以下の実体は不要で、コンパイルも出来るようになります。
 */
/*
void Stream::SetBase(){
	cout << "Stream::SetBase" << endl;
	m_n = -1;
}
*/
