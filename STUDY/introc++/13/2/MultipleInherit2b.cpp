/*
 * 多重継承について
 * 同じクラスを２つ以上継承させる方法について
 *
 * 基底クラスABaseを用意して
 * ABaseを継承するA1クラス、ABaseを継承するA2クラスを準備します。
 * CクラスではA1とA2クラスを継承することによってABaseを２つ継承することができます。
 */
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
class A1 : public ABase {
	public:
		virtual void AHoge(){
			cout << "A1::AHoge" << endl;
		}
};

class A2 : public ABase {
	public:
		virtual void AHoge(){
			cout << "A2::AHoge" << endl;
		}
};

/*
 * A1, A2を継承するCクラス
 */
class C : public A1, public A2 {
};

int main(){
	C c;

	// 以下の２行では両方ともABaseにアップキャストしていることに着目
	ABase& a1 = static_cast<A1&>(c);
	ABase& a2 = static_cast<A2&>(c);

	a1.AHoge();
	a2.AHoge();
}
