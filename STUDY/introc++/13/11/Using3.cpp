#include <iostream>
using namespace std;

class Show {
	public:
		static void Value(char ch)         { cout << ch  << endl; }
		static void Value(const char* str) { cout << str << endl; }
};

class Show2 : public Show {
	public:
		static void Value(char ch){
			int n = static_cast<unsigned char>(ch);
			cout << n << endl;
		}

	// Showクラスを継承したShow2クラスで、Showクラスと同名のメソッド(Value)を定義するとShow側で定義されたValueは使えなくなります。
	// この制約のため、以下のusing構文を入れておくとShow::ValueがShow2クラス内でも利用できるようになります。
	using Show::Value;
};

int main() {
	Show2::Value('A');      // (1) using Show::Value;がなくても実行可能。なぜなら、Show2で定義されたValue(char ch)があるから。
	Show2::Value("Hoge");   // (2) using Show::Value;の行が存在しないとこの行でエラーとなる
}
