/*
 * 参照のダウンキャスト
 *    参考: http://d.hatena.ne.jp/pknight/20090803/1249318452
 *    http://www.geocities.jp/ky_webid/cpp/library/027.html
 *
 */
#include <iostream>
#include <typeinfo>   // for bad_cast

using namespace std;

class CBase {
public:
	virtual ~CBase(){}
};

class CSub : public CBase {
};

int main(){
	CSub obj;
	CBase& objBase = obj;

	try {
		CSub& objSub = dynamic_cast<CSub&>(objBase);
	} catch ( std::bad_cast& e ) {
		cout << "Failed downcast. " << endl;
	}

	return 0;
}
