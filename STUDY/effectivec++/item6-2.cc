// 他のクラスのprivate部分のみを継承することによって、Emptyクラスのコピーコンストラクタとコピー代入演算子の禁止を継承している。
#include<iostream>

// privateとしてコピーコンストラクタ、コピー代入演算子を指定しています。
class Empty{
	public:
		Empty(){};
		~Empty(){};
	private:
		Empty(const Empty& rhs){};
		Empty& operator=(const Empty& rhs){};
};

// Emptyクラスをprivate継承している。
// コピーコンストラクタとコピー代入演算子をprivateにしたクラスをprivate継承することで、コピーを禁止することができるようになる。
class DeprivedEmpty: private Empty {
};

int main(){

	DeprivedEmpty e1;

	// コピーコンストラクタとコピー代入演算子は禁止されている
//	DeprivedEmpty e2(e1);
//	DeprivedEmpty e3;
//	e3 = e2;

}
