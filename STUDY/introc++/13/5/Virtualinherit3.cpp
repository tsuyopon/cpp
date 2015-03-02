#include<iostream>
using namespace std;

/*
 * 基底クラスABase
 */
class ABase {
	public:
		virtual ~ABase(){}
		virtual void AHoge() = 0;
};

/*
 * ABaseを継承するA1, A2クラス
 */
class A1 : virtual public ABase {
	public:
		virtual void AHoge(){
			cout << "A1::AHoge" << endl;
		}
};

class A2 : virtual public ABase {
	public:
		virtual void AHoge(){
			cout << "A2::AHoge" << endl;
		}
};

/*
 * A1, A2を継承するCクラス
 */
class C : public A1, public A2 {

	// CクラスでA1, A2の複数クラスを多重継承しているような場合、
	// AHoge()をオーバーライドしないとA1側のAHoge()を呼び出すか、A2側のAHoge()を呼び出すかわかりませんのでコンパイルエラーとなります。
	public: void AHoge(){
		cout << "C::Ahoge" << endl;
		A1::AHoge();
		A2::AHoge();
	}
};

int main(){
	C c;
	ABase& a = c;
	c.AHoge();
}
