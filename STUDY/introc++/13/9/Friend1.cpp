#include<iostream>
using namespace std;

class Value {

	// ValueFactoryクラスではValueクラスのprivateでも自由にアクセスすることができるようになります。
	friend class ValueFactory;

	public:
		int Get() const { return m_n; }

	private:
		Value(int n) : m_n(n) {}
		Value(const Value&);            // コピーコンストラクタを殺します
		void operator=(const Value&);   // 代入演算子を殺します
		int m_n;
};

class ValueFactory{
	public:
		Value* New(int n) const {
			return new Value(n);      // ValueFactoryクラスはValueクラスでfriend宣言されているのでprivateメソッド・変数にアクセスできる
		}
};

#define ARRAY_SIZE(array) (sizeof(array) / sizeof*(array))

int main(){
	static const int VALUE[] = {
		1, 2, 4, 8,
	};
	static const int SIZE = ARRAY_SIZE(VALUE);

	ValueFactory factory;
	for(int i = 0; i < SIZE; ++i){
		Value* value = factory.New(VALUE[i]);
		cout << value->Get() << ' ';
		delete value;
	}
	cout << endl;
}
