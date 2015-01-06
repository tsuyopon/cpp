#include <iostream>
using namespace std;

class Count {
	public:
		Count();
		virtual ~Count();
		void Show();

	private:
		int m_count = 0;
};

Count::Count(){
	++m_count;
}

Count::~Count(){
	--m_count;
}

void Count::Show(){
	cout << m_count << endl;
}

int main(){
	Count a;
	a.Show();

	// local scope
	{
		Count b;
		a.Show();
		b.Show();
	}
	a.Show();
}
