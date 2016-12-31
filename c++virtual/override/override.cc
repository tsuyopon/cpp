/*
 * ABaseでShow()にvirtualを付与する意味について
 *    ABaseを継承するA1では継承元でShowが定義されていないのでABase::Showを利用する
 *    ABaseを継承するA2では継承元でShowが定義されているのでオーバーライドしたA2::Showを利用する
 *
 *
 */
#include<iostream>
using namespace std;

class ABase {
	public:
		ABase() : m_x(0) {}
		virtual ~ABase(){}
		virtual void Show(){ cout << "ABase::Show() " << m_x << endl; }  // virtualを付与すると継承元ではこれをオーバーライドできる。
		void Set(int x){ m_x = x; }
	protected:
		int m_x;
};

class A1 : public ABase{};
class A2 : public ABase {
	public:
		void Show(){
			cout << "A2::Show() " << m_x << endl;
		}
};

int main(){
	// A1呼び出し
	A1 *a1 = new A1();
	a1->Set(1);
	a1->Show();
	delete a1;
	
	// A2呼び出し
	A2 *a2 = new A2();
	a2->Set(2);
	a2->Show();
	delete a2;
}
