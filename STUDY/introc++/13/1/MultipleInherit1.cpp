/*
 * 多重継承について
 */
#include<iostream>
using namespace std;

/*
 * Cクラスから継承される基底クラスABase, BBase
 */
class ABase {
	public:
		virtual ~ABase(){}
		virtual void AHoge() = 0;
};

class BBase {
	public:
		virtual ~BBase(){}
		virtual void BHoge() = 0;
};

/*
 * ABase, BBaseを多重継承するCクラス
 */
class C : public ABase, public BBase {
	public:
		virtual void AHoge(){
			cout << "C::AHoge" << endl;
		}
		virtual void BHoge(){
			cout << "C::BHoge" << endl;
		}
};

int main(){
	C c;
	ABase& a = c;
	a.AHoge();

	BBase& b = c;
	b.BHoge();
}
