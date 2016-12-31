#include<iostream>

using namespace std;

class ABase {
	public:
		ABase() : var(0) {}
		virtual ~ABase() {}
		void Set(int x){ var = x; }
	protected:
		int var;
};

// ここにvirtualを付与している。
// virtualを付与するとA1が継承するABaseとA2が継承するABaseは同一のものとして扱われる
class A1 : virtual public ABase{};
class A2 : virtual public ABase{};

class C : public A1, public A2 {
	public:
		void Show(){
			cout << A1::var << ", " << A2::var << endl;
		}
};

int main(){
	C c;
	A1& a1 = c;
	A2& a2 = c;
	a1.Set(1);
	c.Show();
	a2.Set(2);
	c.Show();
}
