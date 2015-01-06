/*
 * constオブジェクトのメンバ変数は変更することができませんが、まれに値を変更したい場合があります。
 * このような時には、メンバ変数の型にmutable(変更可能な)という記憶クラス指定子を加えます。
 * これにより、constオブジェクトであってもメンバ変数の内容を変更することができます。
 *
 */
class Test{
	public:
		void Hoge() const;

	private:
		mutable int m_hoge;    // mutable definition
};

void Test::Hoge() const {
	m_hoge = 0;                // constが指定されたメンバー関数内だがmutableなメンバー変数を変更している。
}

int main(){
	Test test;
	test.Hoge();
}
