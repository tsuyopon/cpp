#include <iostream>
using namespace std;

class Count {
	public:
		Count();
		virtual ~Count();
};

static int m_count;

Count::Count(){
	++m_count;
}

Count::~Count(){
	--m_count;
}

void Show(){
	cout << m_count << endl;
}

int main(){
	Show();
	Count a;
	Show();
	{
		Count b;
		Show();
	}
	Show();
}
