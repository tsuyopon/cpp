// 
// mainclass.init(5)と呼ばれた際に、mainclassのコンストラクタは引数なしが呼ばれるのか、引数ありがよばれるのかを確認しておく
#include <iostream>

class Main {
public:
	Main() {
		std::cout << "main1" << std::endl;
	}

	Main(int test) {
		std::cout << "main2" << std::endl;
	}

	void init(int test){
		std::cout << "init2" << std::endl;
	}

};

class State {
public:
	Main mainclass;
};

int main(){
	State *state = new State();
	state->mainclass.init(5);    // main1を呼び、その後にinit2を呼び出す。
	return 0;
}
