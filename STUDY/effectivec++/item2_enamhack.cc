#include<iostream>

class Hoge {
	private:
		static const double statvar;

		// enum hack
		enum {Num = 5};
		int scores[Num];
};

int main(){
	const double Hoge::statvar = 1.35;
	Hoge hoge();
}
