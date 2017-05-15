#include<iostream>

// クラスの最小宣言は次の通りになる。しかし、C++が自動宣言する関数が存在する。
//class Empty{};

// 上記の宣言は次の宣言と同じ(ただし、getを除く)。必要に応じて必要な関数が生成されることになる。
class Empty{
	public:
		Empty(){};                               // デフォルトコンストラクタ
		Empty(const Empty& rhs){};               // コンストラクタ
		~Empty(){};                              // デストラクタ
		Empty& operator=(const Empty& rhs){};    // コピー代入演算子
//		void get(){ std::cout << "hello" << std::endl;}
};

int main(){

	Empty e1;       // デフォルトコンストラクタ(これは Empty e1(); と同じ)
	Empty e2(e1);   // コピーコンストラクタ
	Empty e3;       // デフォルトコンストラクタ
	e3 = e1;        // コピー代入演算子

//	e1.get();
//	e2.get();
//	e3.get();

}
