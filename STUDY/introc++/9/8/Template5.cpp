#include <iostream>
using namespace std;

// char is "default argument"
template <typename TYPE = char> class FortyTwo {
	public:
		TYPE Get() const;
};

template <typename TYPE> TYPE FortyTwo<TYPE>::Get() const{
	return 42;
}

int main(){
	FortyTwo<> ch;                // Don't target TYPE. This case will be use default argument.
	FortyTwo<int> i;
	cout << ch.Get() << endl;
	cout << i.Get() << endl;
}
