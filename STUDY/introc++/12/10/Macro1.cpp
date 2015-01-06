#include <iostream>
using namespace std;

#define FIVE_TIMES for(int i_ = 0; i_ < 5; ++i_)

int main(){
	FIVE_TIMES{
		cout << "Hello World" << endl;
	}
}
