#include <stdio.h>

int var = 100;

class TestClass {
	private:
		int& classVal;
	public:
		// InitializationList
		// See http://www.geocities.co.jp/bleis_tift/cpp/init.html
		//     http://homepage2.nifty.com/well/Reference.html
		// 
		// Constructer(arg) : MemberName(InitValue)
		TestClass() : classVal(var){
			printf("var: %d\n", var);
			printf("classVar: %d\n", classVal);
		}
};

int main(){
	new TestClass();

}
