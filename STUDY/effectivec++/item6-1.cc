// コピーコンストラクタとコピー代入演算子を禁止したい場合の方法について
// 自動で生成されてしまうのを防ぐためには上記をprivateとして宣言すれば良い。
#include<iostream>

// コピーコンストラクタとコピー代入演算子の利用は禁止したいのでprivateに記述する。
class Empty{
	public:
		Empty(){};   // デフォルトコンストラクタ
		~Empty(){};                                 // デストラクタ
	private:
		Empty(const Empty& rhs){};                  // コンストラクタ
		Empty& operator=(const Empty& rhs){};       // コピー代入演算子
};

int main(){

	Empty e1;  // デフォルトコンストラクタ(これは Empty e1(); と同じ)

// 以下は禁止しているのでコメントを外すとコンパイルエラーとなる。
//	Empty e2(e1);   // コピーコンストラクタ
//	Empty e3;       // デフォルトコンストラクタ
//	e3 = e1;        // コピー代入演算子

}
