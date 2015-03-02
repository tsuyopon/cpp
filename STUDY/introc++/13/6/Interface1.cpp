#include<iostream>
#include<sstream>
#include<string>

using namespace std;

/*
 * 以下のクラスは仮想デストラクタ意外には純粋仮想関数しか存在していないクラスです。
 * このようなクラスをインタフェースクラスと呼びます。
 */
class IObject {
	public:
		virtual ~IObject(){}
		virtual string GetString() const = 0;
};

ostream& operator<<(ostream& ostr, const IObject& obj){
	return ostr << obj.GetString();
}

/*
 * IIntとIDoubleの２つのクラスはIObjectインタフェースクラスを継承するクラスです。
 */
class IInt : virtual public IObject {
	public:
		virtual int GetInt() const = 0;
};

class IDouble : virtual public IObject {
	public:
		virtual double GetDouble() const = 0;
};

/*
 * double値を保存しておくだけのくらすDouble
 * IIntとIDoubleを同時に継承しています。
 */
class Double : 
	virtual public IInt,
	virtual public IDouble 
{
	public:
		Double(double x) : m_x(x) {}

	public:
		virtual string GetString() const {
			ostringstream ostr;
			ostr << "Double(" << m_x << ")";
			return ostr.str();
		}

		virtual int GetInt() const {
			return static_cast<int>(m_x);
		}

		virtual double GetDouble() const {
			return m_x;
		}

	private:
		const double m_x;
};

void ShowInt(const IInt& obj){
	cout << "int: " << obj.GetInt() << endl;
}

void ShowDouble(const IDouble& obj){
	cout << "double: " << obj.GetDouble() << endl;
}

int main(){
	Double n = 1.2;
	cout << n << endl;
	ShowInt(n);
	ShowDouble(n);
}
