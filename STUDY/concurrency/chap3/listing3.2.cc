#include<iostream>
#include<mutex>
#include<thread>

class some_data
{
	int a;
	std::string b;
public:
	void do_something();
};

void some_data::do_something(){
	a = 10;
	b = "hoge";
	std::cout << "Executed do_something" << std::endl;
}

class data_wrapper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function> void process_data(Function func){
		std::lock_guard<std::mutex> l(m);
		func(data);   // 1. privateなデータをユーザー定義関数に渡す(Don’t pass pointers and references to protected data outside the scope of the loc)
		
	}
};

some_data* unprotected;

// private
void malicious_functions(some_data& protected_data){
	unprotected = &protected_data;          // 付け替えが行われる
}

data_wrapper x;

void foo(){
	x.process_data(malicious_functions);    // 2. malicious_functionsという悪意のある関数が呼ばれる
	unprotected->do_something();            // 3. privateなはずのオブジェクトにアクセスできてしまう。
}

int main(){
	foo();
}
