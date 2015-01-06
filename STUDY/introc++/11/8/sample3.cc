/*
 * sample1.ccやsample2.ccのAt関数を[]によって置き換えることによってv.At(i)をv[i]としてアクセスできるように
 */
#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

class IntArray {

	public:
		IntArray(int size);
		~IntArray();

		// operatorの定義。忘れやすいので注意
		int &operator[](int i);
		const int& operator[](int i) const;

	public:
		void CheckIndex(int i) const;
		int* At(int i);

	private:
		int* m_array;
		int m_size;
};

IntArray::IntArray(int size){
	m_array = new int[size];
	m_size = size;

	cout << "called constructer. element count is " << m_size << endl;
}

IntArray::~IntArray(){
	delete [] m_array;
	cout << "called destructer. element count is " << m_size << endl;
}

void IntArray::CheckIndex(int i) const{
	if( 0 <= i && i < m_size ){
		cout << "check ok: value=" << i << endl;
	} else {
		cout << "index is invalid. value=" << i << endl;
		exit(EXIT_FAILURE);
	}
}

////////////////////////////////////////////////////////////////////
// [] operatorの定義
////////////////////////////////////////////////////////////////////
int &IntArray::operator[](int i){
	cout << "[] operator1 start." << endl;
	CheckIndex(i);
	cout << m_array[i] << endl;
	return m_array[i];

}

// 呼び出されるオブジェクトがconstオブジェクトであることも考慮して以下も宣言しておきます。
// 後者のconstはメンバー変数を変更しないことを表しています。
const int& IntArray::operator[](int i) const {  
	cout << "[] operator2 start." << endl;
	CheckIndex(i);                        // ここで呼び出すメンバー関数もconstが指定されている必要があるので適切に指定
	return m_array[i];
}

int main(){
	cout << "MAIN START" << endl;
	IntArray v(5);
	cout << "INPUT INTEGER > " << flush;
	cin >> v[1];
	cout << "MAIN inputvalue=" << v[1] << endl;
	return true;

}

