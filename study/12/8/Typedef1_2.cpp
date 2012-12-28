/*
 * Typedef1.cppの改良版です。
 * 出力結果の型にはTypedefされた型を利用しています。 
 */
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// typedefを追加. int やfloatにして " 3 / 2 "等の出力結果を比較してみてください。
typedef int ValueType;
//typedef float ValueType;

class Calculator {
	public:
		void Run();

	private:
		bool Input();
		bool Calculate();
		void ShowResult() const;

	private:
		ValueType m_a, m_b;    // ValueType型に変更
		ValueType m_result;    // ValueType型に変更
		char m_op;
};

void Calculator::Run(){
	while(Input()) {
		if(Calculate()){
			ShowResult();
		}
	}
}

bool Calculator::Input(){
	istringstream isstr;
	while(true){
		string line;
		cout << "Input formula > " << flush;
		getline(cin, line);
		if(cin.fail() || line.empty()){
			return false;
		}

		isstr.clear();
		isstr.str(line);
		isstr >> m_a >> m_op >> m_b;
		if(isstr.fail()){
			continue;
		}
		isstr >> line;
		if(isstr.fail()){
			break;
		}
	}
	return true;
}

bool Calculator::Calculate(){
	switch(m_op){
		case '+': m_result = m_a + m_b; break;
		case '-': m_result = m_a + m_b; break;
		case '*': m_result = m_a + m_b; break;
		case '/':
			if(m_b == 0){
				cerr << "Could not devide by 0." << endl;
				return false;
			}
			m_result = m_a / m_b;
			break;
		default:
			cerr << "Invalid" << endl;
			return false;
	}
	return true;
}

void Calculator::ShowResult() const {
	cout << m_result << endl;
}

int main(){
	Calculator calc;
	calc.Run();
}
